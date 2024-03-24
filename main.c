/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - Basic Input demo -- reads from control pad and indicates button
 *          presses.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 * Copyright (c) 2005 Donour Sizemore <donour@uchicago.edu>
 *
 */
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <stdlib.h>
#include <string.h>

#include "gamePadCheck.h"

#define VERSION_MAJOR 1
#define VERSION_MINOR 0

/* Define the module info section */
PSP_MODULE_INFO("PSP Checker", PSP_MODULE_USER, VERSION_MAJOR, VERSION_MINOR);
//PSP_MODULE_INFO("PSP Checker", PSP_MODULE_KERNEL, VERSION_MAJOR, VERSION_MINOR); //No Kernel Mode for EBOOT in 6.60 :(

/* Define the main thread's attribute value (optional) */
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_VFPU);

int interupted = 0;
int running = 1;

/* Exit callback */
int exit_callback(int arg1, int arg2, void *common)
{
	interupted = 1;
	return 0;
}

/* Callback thread */
int CallbackThread(SceSize args, void *argp)
{
	int cbid;

	cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);
	sceKernelSleepThreadCB();

	return 0;
}

/* Sets up the callback thread and returns its thread id */
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

int main(void)
{
	

	pspDebugScreenInit();
	SetupCallbacks();

	gamePadCheck_init();

	while(running){
		if(interupted) {
			running = 0;
		}
		pspDebugScreenSetXY(0, 2);

		gamePadCheck_cycle();
	}

	sceKernelExitGame();
	return 0;
}
