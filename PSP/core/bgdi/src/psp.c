/* 
 * File:   psp.c
 * Author: danielt3
 *
 * Created on 25 de Dezembro de 2010, 02:27
 */

#include <stdio.h> //for stderr
#include "psp.h"

    /**
     * Define the module info section
     *
     * 2nd arg must 0x1000 so __init is executed in
     * kernelmode for our loaderInit function
     */
    #ifndef USERSPACE_ONLY
            PSP_MODULE_INFO("BGDI-PSP", 0x1000, 1, 1);
    #else
            PSP_MODULE_INFO("BGDI-PSP", 0, 1, 1);
    #endif

    /**
     * THREAD_ATTR_USER causes the thread that the startup
     * code (crt0.c) starts this program in to be in usermode
     * even though the module was started in kernelmode
     */
    #ifndef USERSPACE_ONLY
            PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);
    #endif

    #ifndef USERSPACE_ONLY
    void MyExceptionHandler(PspDebugRegBlock *regs)
    {
            /* Do normal initial dump, setup screen etc */

            pspDebugScreenInit();

            pspDebugScreenSetBackColor(0x00FF0000);
            pspDebugScreenSetTextColor(0xFFFFFFFF);
            pspDebugScreenClear();

            pspDebugScreenPrintf("Exception Details:\n");
            pspDebugDumpException(regs);

            while (1) ;
    }

    /**
     * Function that is called from _init in kernelmode before the
     * main thread is started in usermode.
     */
    __attribute__ ((constructor)) void loaderInit()
    {
            pspKernelSetKernelPC();
            pspDebugInstallErrorHandler(MyExceptionHandler);
    }
    #endif

/* Exit callback */
SceKernelCallbackFunction exit_callback(int arg1, int arg2, void* common)
{
    fprintf( stderr, "entering exit_callback()...\n");
    running = 0;
    bgdrtm_exit(global_ret);
    return 0;
}

/* Callback thread */
int CallbackThread(SceSize size, void *arg)
{
	int cbid;

	cbid = sceKernelCreateCallback("Exit Callback", (SceKernelCallbackFunction)exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);

	sceKernelSleepThreadCB();
	return 0;
}

/* Sets up the callback thread and returns its thread id */
int SetupCallbacks(void) {
    fprintf( stderr, "PSP: setting up callbacks...\n");
    int thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, THREAD_ATTR_USER, 0);
    if (thid >= 0) {
	sceKernelStartThread(thid, 0, 0);
    }
    return thid;
}


