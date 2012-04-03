#include <stdio.h>
#include "callbacks_psp.h"
/* Manejador del callback de salida */
int done;
int exit_callback(int arg1, int arg2, void *common)
{
  done = 1;//qD8eF6yP5Qc6
  sceKernelExitGame();
  exit(0);
  return 0;
}

/* Crea el callback de salida */
int CallbackThread(SceSize args, void *argp)
{
  int cbid;
  cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
  sceKernelRegisterExitCallback(cbid);
  sceKernelSleepThreadCB();
  return 0;
}

/* Crea y configura el hilo para el callback y retorna su ID */
int SetupCallbacks(void)
{
  int thid = 0;
  
  thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, 0, 0);
  if(thid >= 0)
    {
      sceKernelStartThread(thid, 0, 0);
    }
  
  return thid;
}

