/*
 *  This file is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This file is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 *  Initial release by ColDev. Improvements by Osk.
 */

/* --------------------------------------------------------------------------- */

#include <stdio.h>
#include <sqlite3.h>
#include "bgddl.h"
#include "xstrings.h"


typedef struct
{
  int cols,
      rows;
  int CurrentRow;
  char **pazResult;//internal use
} SqlResult ;


/* ----------------------------------------------------------------- */
/*                   Constant definitions                            */


DLCONSTANT  __bgdexport( mod_sqlite3, constants_def )[] =
{
{"SQLITE_OK", 	    TYPE_INT, 	0}, /* Successful result */
{"SQLITE_ERROR",	TYPE_INT,	1}, /* SQL error or missing database */
{"SQLITE_INTERNAL", TYPE_INT,	2}, /* Internal logic error in SQLite */
{"SQLITE_PERM",	    TYPE_INT,	3}, /* Access permission denied */
{"SQLITE_ABORT",	TYPE_INT,	4}, /* Callback routine requested an abort */
{"SQLITE_BUSY",	    TYPE_INT,	5}, /* The database file is locked */
{"SQLITE_LOCKED",	TYPE_INT,	6}, /* A table in the database is locked */
{"SQLITE_NOMEM",	TYPE_INT,	7}, /* A malloc() failed */
{"SQLITE_READONLY", TYPE_INT,	8}, /* Attempt to write a readonly database */
{"SQLITE_INTERRUPT",TYPE_INT,	9}, /* Operation terminated by sqlite3*/
{"SQLITE_IOERR",	TYPE_INT,  10}, /* Some kind of disk I/Oerror occurred */
{"SQLITE_CORRUPT",  TYPE_INT,  11}, /* Database disk image is malformed */
{"SQLITE_FULL",	    TYPE_INT,  13}, /* Insertion failed ´cos database´s full*/
{"SQLITE_CANTOPEN", TYPE_INT,  14}, /* Unable to open the database file */
{"SQLITE_EMPTY",	TYPE_INT,  16}, /* Database is empty */
{"SQLITE_CONSTRAINT",TYPE_INT, 19}, /* Abort due to constraint violation */
{"SQLITE_MISMATCH", TYPE_INT,  20}, /* Data type mismatch */
{"SQLITE_AUTH",	    TYPE_INT,  23}, /* Authorization denied */
{"SQLITE_NOTADB",	TYPE_INT,  26}, /* File opened that isnt a db file */
{"SQLITE_OPEN_READONLY",TYPE_INT,1},
{"SQLITE_OPEN_READWRITE",TYPE_INT,2},
{"SQLITE_OPEN_CREATE",TYPE_INT,4},
{ NULL          , 0       , 	0  }
} ;


/* ----------------------------------------------------------------- */
/*           Types definitions                                  */

char * __bgdexport( mod_sqlite3, types_def ) =
   "TYPE SqlResult\n"
   " int cols;\n"
   " int rows;\n"
   " int currentRow;\n"
   " pointer pointer pazResult;\n"
   "END\n"
   ;

/* ----------------------------------------------------------------- */
/*                  Function definitions                           */

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{/*
  int i;
  for(i=0; i<argc; i++){
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
*/
  return 0;
}


static int modsqlite3_enableCache(INSTANCE * my, int * params)
{
  return sqlite3_enable_shared_cache(params[0]);
}


static int modsqlite3_openDb (INSTANCE * my, int * params)
{
    sqlite3 *db;
    const char * text = (const char *)string_get (params[0]) ;

    int rc= sqlite3_open_v2(text,&db,params[1],0);
    if( rc==SQLITE_OK ) rc= (int)db;
    else {
	   rc=0;
	   sqlite3_close(db);
	   }

    string_discard (params[0]) ;
    return rc;
}


static int modsqlite3_closeDb (INSTANCE * my, int * params)
{
    if (params[0]) sqlite3_close((sqlite3 *)params[0]);
    return 1;
}


static int modsqlite3_execDb (INSTANCE * my, int * params)
{
  char *zErrMsg = 0;
  const char * text = (const char *)string_get (params[1]) ;

  int  rc = sqlite3_exec((sqlite3 *)params[0],text, callback, 0, &zErrMsg);

  if( rc!=SQLITE_OK ){
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }
  string_discard (params[1]) ;
  return rc;
}


static int modsqlite3_openTable (INSTANCE * my, int * params)
{
  char *zErrMsg = 0;
  const char * text = (const char *)string_get (params[1]) ;
  SqlResult *resultado= (SqlResult *)params[2];

  int  rc = sqlite3_get_table((sqlite3 *)params[0],text,&resultado->pazResult, &resultado->rows ,&resultado->cols,&zErrMsg);

  if( rc!=SQLITE_OK ){
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }
  resultado->CurrentRow=1;
  string_discard (params[1]) ;
  return rc;
}


static int modsqlite3_closeTable (INSTANCE * my, int * params)
{
  SqlResult *resultado= (SqlResult *)params[0];

  sqlite3_free_table(resultado->pazResult);
  return 1;
}


static int modsqlite3_getFieldName (INSTANCE * my, int * params)
{
  SqlResult *resultado= (SqlResult *)params[0];
  int res=0;

  res= string_new("");
  string_concat (res,resultado->pazResult[params[1]]);
  string_use(res) ;
  return res;
}


static int modsqlite3_getFieldValue (INSTANCE * my, int * params)
{
  SqlResult *resultado= (SqlResult *)params[0];
  int res=0;
  int i=(resultado->cols * resultado->CurrentRow)+ params[1];

  res= string_new("");
  if (resultado->pazResult[i])
       string_concat (res,resultado->pazResult[i]);

  string_use(res) ;
  return res;
}


static int modsqlite3_lastId (INSTANCE * my, int * params)
{
  return sqlite3_last_insert_rowid((sqlite3*)params[0]);
}


static int modsqlite3_totalChanges(INSTANCE * my, int * params)
{
  return sqlite3_total_changes((sqlite3*)params[0]);
}


static int modsqlite3_errMsg (INSTANCE * my, int * params)
{
  int res=0;
  const char *cad= sqlite3_errmsg((sqlite3*)params[0]);

  res= string_new("");
  string_concat (res,cad);
  string_use(res) ;
  return res;
}

/* --------------------------------------------------------------------------- */

DLSYSFUNCS  __bgdexport( mod_sqlite3, functions_exports )[] =
{
{"SQLITE3_ENABLECACHE",	"I",	 TYPE_DWORD,	modsqlite3_enableCache},
{"SQLITE3_OPEN", 		"SI",    TYPE_DWORD, 	modsqlite3_openDb},
{"SQLITE3_CLOSE", 		"I", 	 TYPE_DWORD, 	modsqlite3_closeDb},
{"SQLITE3_EXEC", 		"IS",    TYPE_DWORD, 	modsqlite3_execDb},
{"SQLITE3_OPENTABLE", 	"ISP",   TYPE_DWORD, 	modsqlite3_openTable},
{"SQLITE3_CLOSETABLE", 	"P", 	 TYPE_DWORD, 	modsqlite3_closeTable},
{"SQLITE3_GETFIELDNAME", "PI",    TYPE_STRING,	modsqlite3_getFieldName},
{"SQLITE3_GETFIELDVALUE", "PI",   TYPE_STRING,	modsqlite3_getFieldValue},
{"SQLITE3_LASTID", 	    "I", 	 TYPE_DWORD, 	modsqlite3_lastId},
{"SQLITE3_TOTALCHANGES", "I", 	 TYPE_DWORD,	modsqlite3_totalChanges},
{"SQLITE3_ERRMSG", 	    "I",     TYPE_STRING,	modsqlite3_errMsg},
{ 0            		, 0     , 0         , 0              }
};


/*Pendientes: sqlite_get_table, sql_prepare,step,reset y finalize, sqlite_bind_tipodato, sqlite_column_count ,sqlite_column_tipodato...
Consultar: http://www.sqlite.org/c3ref/funclist.html
Consultar: http://www.sqlite.org/c3ref/objlist.html
Consultar: http://www.sqlite.org/c3ref/constlist.html
Consultar: http://www.sqlite.org/cintro.html*/

/* --------------------------------------------------------------------------- */
