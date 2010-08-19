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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL_stdinc.h>
/* Bennu specifics */
#include <xstrings.h>
#include <bgddl.h>
#include <errno.h>
#include <sysprocs_st.h>

#ifndef __MONOLITHIC__
#include "iconv_symbols.h"
#endif

//Convert the charset of the string.
//Acceptable params are:
//string fromcharset, string tocharset, string translate_string
CONDITIONALLY_STATIC int bgd_iconv(INSTANCE * my, int * params) {
  size_t inbytesleft, outbytesleft, retval;
  SDL_iconv_t cd;
  const char *inchar = string_get( params[2] );
  char *outchar;
  char *incharptr, *outcharptr;
  int strid=0, close_retval=0;

  //Conversion descriptor
//  printf("fromcode: %s.\n", string_get(params[1]));
//  printf("tocode  : %s.\n", string_get(params[0]));
  cd = SDL_iconv_open( string_get(params[1]), string_get(params[0]) );
  string_discard(params[0]);
  string_discard(params[1]);
  string_discard(params[2]);
  if(cd == (SDL_iconv_t)(-1)) {
    printf("FATAL: couldn't start libiconv, errno: ");
    if(errno == EINVAL) printf("EINVAL (Translation not supported).\n");
    return errno;
  }
    
  /* One should reset the conversion description here, as it might be
     carrying stale info around from previous invocations. */
  SDL_iconv(cd, NULL, NULL, NULL, NULL);

  /* inbytesleft counts the bytes we have not converted yet */
  /* maybe there's a faster way in fenix to get the string length? I
     think fenix already holds this info somewhere anyway */
  inbytesleft = strlen(inchar);
  /* I am not entirely sure 8 can be reached, but just to be on the
     safe side. 4 could also be resonable here, if no crazy
     scripts/encodings are used */
  outbytesleft = inbytesleft * 8;
  outchar = malloc(outbytesleft+1);

  //Couldn't malloc, we better quit
  if (!outchar) {
    SDL_iconv_close(cd);
    fprintf(stdout, "FATAL: Couldn't allocate memory for string conversion\n");
  }

  incharptr = (char*)inchar;
  outcharptr = outchar;
  
  while(1) {
    retval = SDL_iconv(cd, &incharptr, &inbytesleft, &outcharptr, &outbytesleft);
    
    //Handle an error, in case we got one
    /* perror is your friend... (but see also strerror) */
    if(retval == (size_t)-1) {
      perror("iconv");
      break;
    }

    if(inbytesleft == 0)
      break;
  }

  /* Make the string zero-ended */
  *outcharptr = 0;
  
  //Deallocate conversion descriptor
  close_retval = SDL_iconv_close(cd);
  if(close_retval == -1)
    return errno;

  //Return the converted string
  strid = string_new(outchar);
  string_use(strid);
  free(outchar);
  return strid;
}
