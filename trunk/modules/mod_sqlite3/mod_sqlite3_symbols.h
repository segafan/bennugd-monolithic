/*
 *  Copyright © 2006-2011 SplinterGU (Fenix/Bennugd)
 *  Copyright © 2002-2006 Fenix Team (Fenix)
 *  Copyright © 1999-2002 José Luis Cebrián Pagüe (Fenix)
 *
 *  This file is part of Bennu - Game Development
 *
 *  Bennu is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  Bennu is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 */

#ifndef __MODSQLITE3_SYMBOLS_H
#define __MODSQLITE3_SYMBOLS_H

#include <bgddl.h>

#ifndef __BGDC__
extern CONDITIONALLY_STATIC int modsqlite3_enableCache(INSTANCE * my, int * params);
extern CONDITIONALLY_STATIC int modsqlite3_openDb (INSTANCE * my, int * params);
extern CONDITIONALLY_STATIC int modsqlite3_closeDb (INSTANCE * my, int * params);
extern CONDITIONALLY_STATIC int modsqlite3_execDb (INSTANCE * my, int * params);
extern CONDITIONALLY_STATIC int modsqlite3_openTable (INSTANCE * my, int * params);
extern CONDITIONALLY_STATIC int modsqlite3_closeTable (INSTANCE * my, int * params);
extern CONDITIONALLY_STATIC int modsqlite3_getFieldName (INSTANCE * my, int * params);
extern CONDITIONALLY_STATIC int modsqlite3_getFieldValue (INSTANCE * my, int * params);
extern CONDITIONALLY_STATIC int modsqlite3_lastId (INSTANCE * my, int * params);
extern CONDITIONALLY_STATIC int modsqlite3_totalChanges(INSTANCE * my, int * params);
extern CONDITIONALLY_STATIC int modsqlite3_errMsg (INSTANCE * my, int * params);
#endif

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
{"SQLITE_FULL",	    TYPE_INT,  13}, /* Insertion failed Žcos databaseŽs full*/
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

char __bgdexport( mod_sqlite3, types_def )[] =
   "TYPE SqlResult\n"
   " int cols;\n"
   " int rows;\n"
   " int currentRow;\n"
   " pointer pointer pazResult;\n"
   "END\n"
   ;

DLSYSFUNCS  __bgdexport( mod_sqlite3, functions_exports )[] =
{
{"SQLITE3_ENABLECACHE",	"I",	 TYPE_DWORD,	SYSMACRO(modsqlite3_enableCache)},
{"SQLITE3_OPEN", 		"SI",    TYPE_DWORD, 	SYSMACRO(modsqlite3_openDb)},
{"SQLITE3_CLOSE", 		"I", 	 TYPE_DWORD, 	SYSMACRO(modsqlite3_closeDb)},
{"SQLITE3_EXEC", 		"IS",    TYPE_DWORD, 	SYSMACRO(modsqlite3_execDb)},
{"SQLITE3_OPENTABLE", 	"ISP",   TYPE_DWORD, 	SYSMACRO(modsqlite3_openTable)},
{"SQLITE3_CLOSETABLE", 	"P", 	 TYPE_DWORD, 	SYSMACRO(modsqlite3_closeTable)},
{"SQLITE3_GETFIELDNAME", "PI",    TYPE_STRING,	SYSMACRO(modsqlite3_getFieldName)},
{"SQLITE3_GETFIELDVALUE", "PI",   TYPE_STRING,	SYSMACRO(modsqlite3_getFieldValue)},
{"SQLITE3_LASTID", 	    "I", 	 TYPE_DWORD, 	SYSMACRO(modsqlite3_lastId)},
{"SQLITE3_TOTALCHANGES", "I", 	 TYPE_DWORD,	SYSMACRO(modsqlite3_totalChanges)},
{"SQLITE3_ERRMSG", 	    "I",     TYPE_STRING,	SYSMACRO(modsqlite3_errMsg)},
{ 0            		, 0     , 0         , 0              }
};

#endif
