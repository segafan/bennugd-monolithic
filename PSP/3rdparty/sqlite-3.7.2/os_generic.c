/*
** 2010 August 28
**
** The author disclaims copyright to this source code.  In place of
** a legal notice, here is a blessing:
**
**    May you do good and not evil.
**    May you find forgiveness for yourself and forgive others.
**    May you share freely, never taking more than you give.
**
******************************************************************************
**
** This file contains code that is specific to the Nintendo ds.
*/
#include <unistd.h> // for MAXPATHLEN
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/errno.h>


#include "sqlite3.h"

#define NO_LOCK         0
#define SHARED_LOCK     1
#define RESERVED_LOCK   2
#define PENDING_LOCK    3
#define EXCLUSIVE_LOCK  4

#define NO_ERROR 0
#define SQLITE_OK 0

#ifndef SQLITE_DEFAULT_SECTOR_SIZE
# define SQLITE_DEFAULT_SECTOR_SIZE 512
#endif

typedef struct genFile genFile;

struct genFile {
  const struct sqlite3_io_methods *pMethods;  /* Methods for an open file *//* Always the first entry */
  FILE* file;    /* Handle for accessing the file */
  char* pathToDel;          /* Name of file to delete on close, NULL if not */
  unsigned char locktype;   /* Type of lock currently held on this file */
};


/*****************************************************************************
** The next group of routines implement the I/O methods specified
** by the sqlite3_io_methods object.
******************************************************************************/
/*
** Close a file.
*/
static int genClose( sqlite3_file *id ){

  int rc = NO_ERROR;
  genFile *pFile;
  if( id && (pFile = (genFile*)id) ){
    rc = fclose(pFile->file);
    pFile->locktype = NO_LOCK;
    if (pFile->pathToDel){
      unlink(pFile->pathToDel);
      free(pFile->pathToDel);
      pFile->pathToDel = NULL;
    }
    id = 0;
  }
  return rc == NO_ERROR ? SQLITE_OK : SQLITE_IOERR;
}

/*
** Read data from a file into a buffer.  Return SQLITE_OK if all
** bytes were read successfully and SQLITE_IOERR if anything goes
** wrong.
*/
static int genRead(
  sqlite3_file *id,               /* File to read from */
  void *pBuf,                     /* Write content into this buffer */
  int amt,                        /* Number of bytes to read */
  sqlite3_int64 offset            /* Begin reading at this offset */
){

  size_t nBytes;
  genFile *pFile = (genFile*)id;
  if(fseek(pFile->file, offset, SEEK_SET)) return SQLITE_IOERR;

  nBytes = fread(pBuf, 1, amt, pFile->file);
  if (nBytes==amt) return SQLITE_OK;

  int error = ferror(pFile->file);
  if (error) return SQLITE_IOERR_READ;
  /* Unread portions of the input buffer must be zero-filled */
  memset(&((char*)pBuf)[nBytes], 0, amt-nBytes);
  return SQLITE_IOERR_SHORT_READ; 
}

/*
** Determine the current size of a file in bytes
*/
static int genFileSize( sqlite3_file *id, sqlite3_int64 *pSize ){
  FILE* file = ((genFile*)id)->file;
  struct stat myStats; 
  memset(&myStats, 0, sizeof(myStats));

  if (fstat(file->_file, &myStats)) return SQLITE_IOERR_FSTAT;
  *pSize = myStats.st_size;
  return SQLITE_OK;
}

/*
** Write data from a buffer into a file.  Return SQLITE_OK on success
** or some other error code on failure.
*/
static int genWrite(
  sqlite3_file *id,               /* File to write into */
  const void *pBuf,               /* The bytes to be written */
  int amt,                        /* Number of bytes to write */
  sqlite3_int64 offset            /* Offset into the file to begin writing at */
){

    int rc = 0;
  genFile *pFile = (genFile*)id;
  if(fseek(pFile->file, offset, SEEK_SET)) return SQLITE_IOERR;
   while( amt > 0 &&
         (rc = fwrite(pBuf, 1, amt, pFile->file)) && (rc>0))
  {
    amt -= rc;
    pBuf = &((char*)pBuf)[rc];
  }
  if (rc<=0) return SQLITE_IOERR;
  return (amt>0) ? SQLITE_FULL : SQLITE_OK;
}

/*
** Truncate an open file to a specified size
*/
static int genTruncate( sqlite3_file *id, sqlite3_int64 nByte ){

  int rc = NO_ERROR;
  FILE *file = ((genFile*)id)->file;
  rc = ftruncate(file->_file, nByte);
  return rc == NO_ERROR ? SQLITE_OK : SQLITE_IOERR_TRUNCATE;
}

/*
** Make sure all writes to a particular file are committed to disk.
*/
static int genSync( sqlite3_file *id, int flags ){

  genFile *pFile = (genFile*)id;
  /* If we compiled with the SQLITE_NO_SYNC flag, then syncing is a
  ** no-op
  */
#ifdef SQLITE_NO_SYNC
  UNUSED_PARAMETER(pFile);
  return SQLITE_OK;
#else
  return fsync(pFile->file->_file) == NO_ERROR ? SQLITE_OK : SQLITE_IOERR;
#endif
}


/*
** Return the sector size in bytes of the underlying block device for
** the specified file. This is almost always 512 bytes, but may be
** larger for some devices.
**
** SQLite code assumes this function cannot fail. It also assumes that
** if two files are created in the same file-system directory (i.e.
** a database and its journal file) that the sector size will be the
** same for both.
*/
static int genSectorSize(sqlite3_file *id){
  return SQLITE_DEFAULT_SECTOR_SIZE;
}

/*
** Return a vector of device characteristics.
*/
static int genDeviceCharacteristics(sqlite3_file *id){
  return 0;
}

  int genLock(sqlite3_file* file, int gah7) {return SQLITE_OK;}; 
  int genUnlock(sqlite3_file* file, int gah8) {return SQLITE_OK;}; 
  int genCheckReservedLock(sqlite3_file* file, int *pResOut) {return SQLITE_OK;}; 
  int genFileControl(sqlite3_file* file, int op, void *pArg) {return SQLITE_OK;}; 

/*
** This vector defines all the methods that can operate on an
** sqlite3_file for os2.
*/
static const sqlite3_io_methods genIOMethods = {
  1,                        /* iVersion */
  genClose,
  genRead,
  genWrite,
  genTruncate,
  genSync,
  genFileSize,
  genLock,
  genUnlock,
  genCheckReservedLock,
  genFileControl,
  genSectorSize,
  genDeviceCharacteristics
};
/***************************************************************************
** Here ends the I/O methods that form the sqlite3_io_methods object.
**
** The next block of code implements the VFS methods.
****************************************************************************/


unsigned int genTmpFileGobalCount = 0;

static char zTmpname[MAXPATHLEN+1];   /* Buffer to hold name of temp file */
static char __wdir[MAXPATHLEN+1];
/*
** Create a temporary file name in zBuf.  zBuf must be big enough to
** hold at pVfs->mxPathname characters.
*/
int genGetTempname(int nBuf, char *zBuf) {

    genTmpFileGobalCount++;
	strcpy(zTmpname,__wdir);
	
	char *temp = mktemp("tmpXXXXXX");
	strcat(zTmpname,temp);

    if (nBuf < strlen(temp)) return  666;
	strcpy(zBuf,zTmpname);
    
    return SQLITE_OK;
};

int genFullPathname(sqlite3_vfs* vfs, const char *zName, int nOut, char *zOut) {
 
    strcpy(zOut, zName);

    return SQLITE_OK;
}; // FIXTHIS LATER


/*
** Open a file.
*/
static int genOpen(
  sqlite3_vfs *pVfs,           /* The VFS for which this is the xOpen method */
  const char *zName,           /* Pathname of file to be opened */
  sqlite3_file *id,         /* The file descriptor to be filled in */
  int flags,                   /* Input flags to control the opening */
  int *pOutFlags               /* Output flags returned to SQLite core */
){
    genFile *pFile = (genFile*)id;
    FILE* file = NULL; 
    int rc = NO_ERROR;            /* Function Return Code */
    pFile->pMethods = &genIOMethods;      
    
    char zTmpname[MAXPATHLEN+1];   /* Buffer to hold name of temp file */
  
    /* If the second argument to this function is NULL, generate a 
    ** temporary file name to use 
    */
    if( !zName ){
        /* If zName is NULL, the upper layer is requesting a temp file. */
        rc = genGetTempname(MAXPATHLEN + 1, zTmpname);
        if(rc != SQLITE_OK ) return rc;
        zName = zTmpname;
    }
    
   memset(pFile, 0, sizeof(*pFile));    
    
      if( flags & SQLITE_OPEN_DELETEONCLOSE ){
          char pathUtf8[MAXPATHLEN+1];
          genFullPathname( pVfs, zName, MAXPATHLEN, pathUtf8 );
          pFile->pathToDel = pathUtf8;
      }else{
          pFile->pathToDel = NULL;
      }
   
      if( pOutFlags ){
        *pOutFlags = flags;
    }    

      if((flags & SQLITE_OPEN_READWRITE)) {
           file = fopen(zName, "rb+");
           if (!file) {

               if (flags & SQLITE_OPEN_CREATE) {
                   file = fopen(zName, "wb+");
               }
               else { 
                   file = fopen(zName, "rb");
                   *pOutFlags |= SQLITE_OPEN_READONLY;           
               }
           } 
      }
      else if(flags & SQLITE_OPEN_READONLY) file = fopen(zName, "rb");
    if (!file) {
       if(pFile->pathToDel) free( pFile->pathToDel );
       pFile->pathToDel = NULL;

       return SQLITE_CANTOPEN;
    }
    pFile->pMethods = &genIOMethods;
    pFile->file = file;
    return SQLITE_OK; 
};


/*
** Delete the named file.
*/
static int genDelete(
  sqlite3_vfs *pVfs,                     /* Not used on os2 */
  const char *zFilename,                 /* Name of file to delete */
  int syncDir                            /* Not used on os2 */
){

  if ((unlink(zFilename)==-1) && (errno!=ENOENT)) return SQLITE_IOERR_DELETE;
  return SQLITE_OK;
}


/*
** Check the existance and status of a file.
*/
static int genAccess(
  sqlite3_vfs *pVfs,        /* Not used on os2 */
  const char *zFilename,    /* Name of file to check */
  int flags,                /* Type of test to make on this file */
  int *pOut                 /* Write results here */
){
 
  int rc = NO_ERROR;
  struct stat myStats; 
  memset(&myStats, 0, sizeof(myStats));
  rc = stat(zFilename, &myStats);
  switch( flags ){
    case SQLITE_ACCESS_READ:
       rc = ((rc == NO_ERROR) && (S_IREAD & myStats.st_mode));
        break;
    case SQLITE_ACCESS_EXISTS:
      rc = (rc == NO_ERROR);
      break;
    case SQLITE_ACCESS_READWRITE:
      rc = ((rc == NO_ERROR) && (S_IREAD & myStats.st_mode) && (S_IWRITE & myStats.st_mode)); 
      break;
    default:
	  return SQLITE_MISUSE;
  }
  *pOut = rc;
  return SQLITE_OK;
}

/*
** Sleep for a little while.  Return the amount of time slept.
** The argument is the number of microseconds we want to sleep.
** The return value is the number of microseconds of sleep actually
** requested from the underlying operating system, a number which
** might be greater than or equal to the argument, but not less
** than the argument.
*/
static int genSleep( sqlite3_vfs *pVfs, int microsec) {
	return microsec;
}

/*
** Find the current time (in Universal Coordinated Time).  Write the
** current time and date as a Julian Day number into *prNow and
** return 0.  Return 1 if the time and date cannot be found.
*/
int genCurrentTime( sqlite3_vfs *pVfs, double *prNow ){

 
  struct tm *greg_time;  /* Time and timezone structure */
  time_t system_time;  /* The system time in seconds from 1970 */
   system_time = time(NULL);
  greg_time = localtime(&system_time);
    double date;  /* A running variable calculating the Julian date */
  int month;    /* The month in the year */
  int day;      /* The day in the month */
  int year;     /* The years from 1900 */

  /* Get the day, month and year from the greg_time structure and form
     them into 1/1/2000 rather than 1/0/100 from greg_time. */

  day = greg_time->tm_mday;
  month = greg_time->tm_mon + 1;
  year = greg_time->tm_year + 1900;

  /* Calculate the Julian days */

  date = day - 32076 + 
    1461*(year + 4800 + (month - 14)/12)/4 +
    367*(month - 2 - (month - 14)/12*12)/12 - 
    3*((year + 4900 + (month - 14)/12)/100)/4;

  /* Add the fractional hours, mins and seconds */
  
  date += (greg_time->tm_hour + 12.0)/24.0;
  date += (greg_time->tm_min)/1440.0;
  date += (greg_time->tm_sec)/86400.0;
   *prNow = date;
#ifdef SQLITE_TEST
  if( sqlite3_current_time ){
    *prNow = sqlite3_current_time/86400.0 + 2440587.5;
  }
#endif
 
  return 0;
}

int genGetLastError(sqlite3_vfs* vfs, int gah9, char * gah4) {

      return 0;
}; // stub


/*
** Write up to nBuf bytes of randomness into zBuf.
*/
static int genRandomness(sqlite3_vfs *pVfs, int nBuf, char *zBuf ){

  int n = 0;
#if defined(SQLITE_TEST)
  n = nBuf;
  memset(zBuf, 0, nBuf);
#else
   int a = time(NULL);
   n= nBuf;
   int i;
   for (i = 0; i < nBuf; ++i) {
       zBuf[i] = (a + i + rand()) & 0xff;
       a += (i+ zBuf[i])>>1 ;
   }
#endif
  return n;
}


/*
** Interfaces for opening a shared library, finding entry points
** within the shared library, and closing the shared library.
*/
void *genDlOpen(sqlite3_vfs* vfs, const char *zFilename) {
return NULL;/* no-op */}; 

void genDlError(sqlite3_vfs* vfs, int nByte, char *zErrMsg) {
/* no-op */}; 

void (*genDlSym(sqlite3_vfs* vfs,void* gah1, const char *zSymbol))(void) {
return NULL;/* no-op */}; 

void genDlClose(sqlite3_vfs* vfs, void* gah2) {


/* no-op */}; 
  


/*
** Initialize and deinitialize the operating system interface.
*/
int sqlite3_os_init(void){

	getcwd(__wdir,MAXPATHLEN);

  static sqlite3_vfs genVfs = {
    1,                 /* iVersion */
    sizeof(genFile),   /* szOsFile */
    MAXPATHLEN,        /* mxPathname */
    NULL,                 /* pNext */
    "generic",             /* zName */
    NULL,                 /* pAppData */

    genOpen,           /* xOpen */
    genDelete,         /* xDelete */
    genAccess,         /* xAccess */
    genFullPathname,   /* xFullPathname */
    genDlOpen,         /* xDlOpen */
    genDlError,        /* xDlError */
    genDlSym,          /* xDlSym */
    genDlClose,        /* xDlClose */
    genRandomness,     /* xRandomness */
    genSleep,          /* xSleep */
    genCurrentTime,    /* xCurrentTime */
    genGetLastError,   /* xGetLastError */
  };
  sqlite3_vfs_register(&genVfs, 1);
  return SQLITE_OK;
}

int sqlite3_os_end(void){

  return SQLITE_OK;
}

int sqlite3_initialize(void);
int sqlite3_shutdown(void);

