#include <taihen.h>
#include <vitasdk.h>
#include <psp2/appmgr.h> 
#include <psp2/ctrl.h> 

static SceUID g_hooks[1];
static unsigned int g_buttonsPressed = 0;
uint32_t text_addr, text_size, data_addr, data_size;

void _start() __attribute__ ((weak, alias ("module_start")));

static tai_hook_ref_t ref_hook0;
static int sceDisplaySetFrameBuf_patched(const SceDisplayFrameBuf *pParam, int sync) {
	SceCtrlData ctrl;
	sceCtrlPeekBufferPositive(0, &ctrl, 1);
	unsigned int buttons = ctrl.buttons & ~g_buttonsPressed;

	if (ctrl.buttons & SCE_CTRL_SELECT) {
		if (buttons & SCE_CTRL_RIGHT)
			sceAppMgrLaunchAppByUri(0xFFFFF, "psgm:play?titleid=MODALVOLM");
		}
	return TAI_CONTINUE(int, ref_hook0, pParam, sync);
}

int module_start(SceSize argc, const void *args){
  g_hooks[0] = taiHookFunctionImport(&ref_hook0,
	TAI_MAIN_MODULE,
	TAI_ANY_LIBRARY,
	0x7A410B64,
	sceDisplaySetFrameBuf_patched);
  return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize argc, const void *args) 
{
	if (g_hooks[0] >= 0) taiHookRelease(g_hooks[0], ref_hook0);
  return SCE_KERNEL_STOP_SUCCESS;
}
