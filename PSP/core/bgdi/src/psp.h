/* ---------------------------------------------------------------------- */
// PSP specific stuff
// mostly based on ScummVM PSP port
/* ---------------------------------------------------------------------- */
#ifndef __PSP_H__
    #define __PSP_H__

    #define USERSPACE_ONLY		//don't use kernel mode features

    #include <psptypes.h>
    #include <pspkernel.h>
    #include <stdarg.h>
    #include <pspdebug.h>

    #include "bgdrtm.h"

    extern int running;
    extern int global_ret;
#endif // __PSP_H__
/* ---------------------------------------------------------------------- */
