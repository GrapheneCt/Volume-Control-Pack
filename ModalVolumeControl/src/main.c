//It seems that app doesn't launch in true modal mode. Maybe there's some additional check in sceShell?

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <vitasdk.h>
#include <psp2/avconfig.h> 
#include <psp2/kernel/threadmgr.h> 
#include <psp2/registrymgr.h> 

#include "debugScreen.h"
#include "ctrl.h"

#define printf psvDebugScreenPrintf

static int currentVolume;

void increaseVolume(int check){
  if (currentVolume == 30 && check == 0) {}
  else if (currentVolume == 21 && check == 1) {}
  else
	  sceAVConfigSetSystemVol(currentVolume + 1);
}

void decreaseVolume(){
  if (currentVolume == 0) {}
  else
	  sceAVConfigSetSystemVol(currentVolume - 1);
}

int main(){
  int avls;
  repeat:
  psvDebugScreenInit();
  sceAVConfigGetSystemVol(&currentVolume);
  sceRegMgrGetKeyInt("/CONFIG/SOUND/", "avls", &avls);
  printf("\n\n--- Modal Volume Control by Graphene ---\n");
  printf("UP: Increase Volume\n");
  printf("DOWN: Decrease Volume\n");
  printf("TRIANGLE: Mute Console\n");
  printf("CROSS: Exit Modal Volume Control\n\n");
  if (avls == 1)
	  printf("AVLS is turned on.\n");
  else
	  printf("                  \n");
  printf("Current Volume: ");
  if (currentVolume < 10)
	  printf("0%d\n", currentVolume);
  else
      printf("%d\n", currentVolume);

      switch(get_key (0)){
	case SCE_CTRL_UP:
	  increaseVolume(avls);
	  break;
	case SCE_CTRL_DOWN:
	  decreaseVolume();
	  break;
	case SCE_CTRL_TRIANGLE:
	  sceAVConfigMuteOn();
	  break;
	case SCE_CTRL_CROSS:
	  sceKernelExitProcess(0);
	  break;
	default:
	  break;
	}
  sceKernelDelayThread(100000);
  goto repeat;
  return 0;
}
