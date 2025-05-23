#ifndef VMANAGER_H
#define VMANAGER_H

#include <windows.h>


inline constexpr GUID DSPROPSETID_VoiceManager{
    0x62a69bae,
    0xdf9d,0x11d1,
    {0x99,0xa6,0x00,0xc0,0x4f,0xc9,0x9d,0x46}
};


enum DSPROPERTY_VMANAGER {
    DSPROPERTY_VMANAGER_MODE = 0,
    DSPROPERTY_VMANAGER_PRIORITY,
    DSPROPERTY_VMANAGER_STATE
};


enum VmMode {
    DSPROPERTY_VMANAGER_MODE_DEFAULT = 0,
    DSPROPERTY_VMANAGER_MODE_AUTO,
    DSPROPERTY_VMANAGER_MODE_REPORT,
    DSPROPERTY_VMANAGER_MODE_USER,
    VMANAGER_MODE_MAX
};


enum VmState {
    DSPROPERTY_VMANAGER_STATE_PLAYING3DHW = 0,
    DSPROPERTY_VMANAGER_STATE_SILENT,
    DSPROPERTY_VMANAGER_STATE_BUMPED,
    DSPROPERTY_VMANAGER_STATE_PLAYFAILED,
    VMANAGER_STATE_MAX
};

#endif // VMANAGER_H
