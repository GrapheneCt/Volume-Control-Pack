# Volume Control Pack
This pack consits of applications to control system audio volume on PS vita in real time. Can be usefull if vol+- buttons are broken:
1. Modal Volume Control application
2. Volume Control application
3. Modal Volume Control plugin (only needed for Modal Volume Control)

All of this applications can be used simultaneously with any games, including the ones that require enlarged memory (with LowMemMode plugin). Runs on system-reserved CPU core.

# Usage
You have two choices:
1. Install VolumeControl.vpk. Can be used right away, plugin is not required. Shell BGM will be played back in the app, allowing for easy volume setup.

2. (Warning! This variant has some dugs and is not recommended for now) Install ModalVol plugin (under * All) and after that install ModalVolumeControl application. Application bubble will not appear in LiveArea, this is normal. Reboot your Vita. You can now launch Modal Volume Control application in most of the games by pressing SELECT + RIGHT button combination.

# How to Build
Use vitasdk to build applications and plugin. After building, boot parameters for applications have to be set manually. To do that:
1. Open eboot.bin in hex editor.
2. Find Control Information type 6 section.
3. Change value at relative offset 0x1D from 0x00 to 0x40. This will force application to launch with low memory budget (Max 14MiB) and change CPU affinity mask to system-reserved core. If you want application to run on all cores, change value at relative offset 0x14 from 0x00 to 0x08.
