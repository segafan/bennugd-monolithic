/* ************************************************************************** */
/* *                                                                        * */
/* *            Copyright (c) 2008-2010 - Joseba García Etxebarria          * */
/* *                                                                        * */
/* *                   This is a BennuGD interface to iconv                 * */
/* *                                                                        * */
/* *            Under the terms of the GNU GPL version 2 license            * */
/* *                                                                        * */
/* *                         See LICENSE for details                        * */
/* *                                                                        * */
/* ************************************************************************** */

#ifndef __MODICONV_SYMBOLS_H
#define __MODICONV_SYMBOLS_H

#include <bgddl.h>

#ifndef __BGDC__
extern CONDITIONALLY_STATIC int bgd_iconv(INSTANCE * my, int * params);
#endif

DLSYSFUNCS __bgdexport( mod_iconv, functions_exports )[] =
{
	{ "ICONV"            , "SSS"  , TYPE_STRING, SYSMACRO(bgd_iconv)       },
	{ 0                  , 0      , 0          , 0                         }
};

#endif
