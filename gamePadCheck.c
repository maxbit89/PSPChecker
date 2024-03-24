#include "gamePadCheck.h"

SceCtrlData padOld;
GamePadCheckReport gamePadCheckReport;

void gamePadCheck_init() {
    sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
    memset(&gamePadCheckReport, 0, sizeof(gamePadCheckReport));
}

bool checkBtnDown(int btn, SceCtrlData* pad, SceCtrlData* padOld) {
    return (pad->Buttons & btn && !(padOld->Buttons & btn));
}

bool checkBtnUp(int btn, SceCtrlData* pad, SceCtrlData* padOld) {
    return (padOld->Buttons & btn && !(pad->Buttons & btn));
}

void formatReportEntry(char* name, GamePadCheckReport *report, void* base, void* element) {
    size_t entryOffset = element - base;
    bool *up   = (bool*)&(report->up) + entryOffset;
    bool *down = (bool*)&(report->down) + entryOffset;
    bool *upActive = (bool*)&(report->upActive) + entryOffset;
    bool *downActive = (bool*)&(report->downActive) + entryOffset;
    pspDebugScreenPrintf("%16s Up:%s Down:%s\n",
        name,
        (*upActive   ? "[<OK>]" : (*up   ? "[ OK ]" : "[WAIT]")),
        (*downActive ? "[<OK>]" : (*down ? "[ OK ]" : "[WAIT]")));
}

void gamePadCheck_cycle() {
    SceCtrlData pad;

    sceCtrlReadBufferPositive(&pad, 1);

    gamePadCheckReport.down.select      |= (gamePadCheckReport.downActive.select      = checkBtnDown(PSP_CTRL_SELECT, &pad, &padOld));
    gamePadCheckReport.down.start       |= (gamePadCheckReport.downActive.start       = checkBtnDown(PSP_CTRL_START, &pad, &padOld));
    gamePadCheckReport.down.up          |= (gamePadCheckReport.downActive.up          = checkBtnDown(PSP_CTRL_UP, &pad, &padOld));
    gamePadCheckReport.down.right       |= (gamePadCheckReport.downActive.right       = checkBtnDown(PSP_CTRL_RIGHT, &pad, &padOld));
    gamePadCheckReport.down.down        |= (gamePadCheckReport.downActive.down        = checkBtnDown(PSP_CTRL_DOWN, &pad, &padOld));
    gamePadCheckReport.down.left        |= (gamePadCheckReport.downActive.left        = checkBtnDown(PSP_CTRL_LEFT, &pad, &padOld));
    gamePadCheckReport.down.lTrigger    |= (gamePadCheckReport.downActive.lTrigger    = checkBtnDown(PSP_CTRL_LTRIGGER, &pad, &padOld));
    gamePadCheckReport.down.rTrigger    |= (gamePadCheckReport.downActive.rTrigger    = checkBtnDown(PSP_CTRL_RTRIGGER, &pad, &padOld));
    gamePadCheckReport.down.triangel    |= (gamePadCheckReport.downActive.triangel    = checkBtnDown(PSP_CTRL_TRIANGLE, &pad, &padOld));
    gamePadCheckReport.down.circle      |= (gamePadCheckReport.downActive.circle      = checkBtnDown(PSP_CTRL_CIRCLE, &pad, &padOld));
    gamePadCheckReport.down.cross       |= (gamePadCheckReport.downActive.cross       = checkBtnDown(PSP_CTRL_CROSS, &pad, &padOld));
    gamePadCheckReport.down.square      |= (gamePadCheckReport.downActive.square      = checkBtnDown(PSP_CTRL_SQUARE, &pad, &padOld));
    gamePadCheckReport.down.home        |= (gamePadCheckReport.downActive.home        = checkBtnDown(PSP_CTRL_HOME, &pad, &padOld));
    gamePadCheckReport.down.hold        |= (gamePadCheckReport.downActive.hold        = checkBtnDown(PSP_CTRL_HOLD, &pad, &padOld));
    gamePadCheckReport.down.note        |= (gamePadCheckReport.downActive.note        = checkBtnDown(PSP_CTRL_NOTE, &pad, &padOld));
    gamePadCheckReport.down.screen      |= (gamePadCheckReport.downActive.screen      = checkBtnDown(PSP_CTRL_SCREEN, &pad, &padOld));
    gamePadCheckReport.down.volUp       |= (gamePadCheckReport.downActive.volUp       = checkBtnDown(PSP_CTRL_VOLUP, &pad, &padOld));
    gamePadCheckReport.down.volDown     |= (gamePadCheckReport.downActive.volDown     = checkBtnDown(PSP_CTRL_VOLDOWN, &pad, &padOld));
    gamePadCheckReport.down.wlan        |= (gamePadCheckReport.downActive.wlan        = checkBtnDown(PSP_CTRL_WLAN_UP, &pad, &padOld));
    gamePadCheckReport.down.remoteHold  |= (gamePadCheckReport.downActive.remoteHold  = checkBtnDown(PSP_CTRL_REMOTE, &pad, &padOld));
    gamePadCheckReport.down.disc        |= (gamePadCheckReport.downActive.disc        = checkBtnDown(PSP_CTRL_DISC, &pad, &padOld));
    gamePadCheckReport.down.memoryStick |= (gamePadCheckReport.downActive.memoryStick = checkBtnDown(PSP_CTRL_MS, &pad, &padOld));
    
    gamePadCheckReport.up.select        |= (gamePadCheckReport.upActive.select = checkBtnUp(PSP_CTRL_SELECT, &pad, &padOld));
    gamePadCheckReport.up.start         |= (gamePadCheckReport.upActive.start = checkBtnUp(PSP_CTRL_START, &pad, &padOld));
    gamePadCheckReport.up.up            |= (gamePadCheckReport.upActive.up = checkBtnUp(PSP_CTRL_UP, &pad, &padOld));
    gamePadCheckReport.up.right         |= (gamePadCheckReport.upActive.right = checkBtnUp(PSP_CTRL_RIGHT, &pad, &padOld));
    gamePadCheckReport.up.down          |= (gamePadCheckReport.upActive.down = checkBtnUp(PSP_CTRL_DOWN, &pad, &padOld));
    gamePadCheckReport.up.left          |= (gamePadCheckReport.upActive.left = checkBtnUp(PSP_CTRL_LEFT, &pad, &padOld));
    gamePadCheckReport.up.lTrigger      |= (gamePadCheckReport.upActive.lTrigger = checkBtnUp(PSP_CTRL_LTRIGGER, &pad, &padOld));
    gamePadCheckReport.up.rTrigger      |= (gamePadCheckReport.upActive.rTrigger = checkBtnUp(PSP_CTRL_RTRIGGER, &pad, &padOld));
    gamePadCheckReport.up.triangel      |= (gamePadCheckReport.upActive.triangel = checkBtnUp(PSP_CTRL_TRIANGLE, &pad, &padOld));
    gamePadCheckReport.up.circle        |= (gamePadCheckReport.upActive.circle = checkBtnUp(PSP_CTRL_CIRCLE, &pad, &padOld));
    gamePadCheckReport.up.cross         |= (gamePadCheckReport.upActive.cross = checkBtnUp(PSP_CTRL_CROSS, &pad, &padOld));
    gamePadCheckReport.up.square        |= (gamePadCheckReport.upActive.square = checkBtnUp(PSP_CTRL_SQUARE, &pad, &padOld));
    gamePadCheckReport.up.home          |= (gamePadCheckReport.upActive.home = checkBtnUp(PSP_CTRL_HOME, &pad, &padOld));
    gamePadCheckReport.up.hold          |= (gamePadCheckReport.upActive.hold = checkBtnUp(PSP_CTRL_HOLD, &pad, &padOld));
    gamePadCheckReport.up.note          |= (gamePadCheckReport.upActive.note = checkBtnUp(PSP_CTRL_NOTE, &pad, &padOld));
    gamePadCheckReport.up.screen        |= (gamePadCheckReport.upActive.screen = checkBtnUp(PSP_CTRL_SCREEN, &pad, &padOld));
    gamePadCheckReport.up.volUp         |= (gamePadCheckReport.upActive.volUp = checkBtnUp(PSP_CTRL_VOLUP, &pad, &padOld));
    gamePadCheckReport.up.volDown       |= (gamePadCheckReport.upActive.volDown = checkBtnUp(PSP_CTRL_VOLDOWN, &pad, &padOld));
    gamePadCheckReport.up.wlan          |= (gamePadCheckReport.upActive.wlan = checkBtnUp(PSP_CTRL_WLAN_UP, &pad, &padOld));
    gamePadCheckReport.up.remoteHold    |= (gamePadCheckReport.upActive.remoteHold = checkBtnUp(PSP_CTRL_REMOTE, &pad, &padOld));
    gamePadCheckReport.up.disc          |= (gamePadCheckReport.upActive.disc = checkBtnUp(PSP_CTRL_DISC, &pad, &padOld));
    gamePadCheckReport.up.memoryStick   |= (gamePadCheckReport.upActive.memoryStick = checkBtnUp(PSP_CTRL_MS, &pad, &padOld));

    pspDebugScreenPrintf("0x%08x 0x%08x\n", pad.Buttons, padOld.Buttons);
    formatReportEntry("Select",      &gamePadCheckReport, &(gamePadCheckReport.up), &(gamePadCheckReport.up.select));
    formatReportEntry("Start",       &gamePadCheckReport, &(gamePadCheckReport.up), &(gamePadCheckReport.up.start));
    formatReportEntry("Up",          &gamePadCheckReport, &(gamePadCheckReport.up), &(gamePadCheckReport.up.up));
    formatReportEntry("Right",       &gamePadCheckReport, &(gamePadCheckReport.up), &(gamePadCheckReport.up.right));
    formatReportEntry("Down",        &gamePadCheckReport, &(gamePadCheckReport.up), &(gamePadCheckReport.up.down));
    formatReportEntry("Left",        &gamePadCheckReport, &(gamePadCheckReport.up), &(gamePadCheckReport.up.left));
    formatReportEntry("LTrigger",    &gamePadCheckReport, &(gamePadCheckReport.up), &(gamePadCheckReport.up.lTrigger));
    formatReportEntry("RTrigger",    &gamePadCheckReport, &(gamePadCheckReport.up), &(gamePadCheckReport.up.rTrigger));
    formatReportEntry("Triangle",    &gamePadCheckReport, &(gamePadCheckReport.up), &(gamePadCheckReport.up.triangel));
    formatReportEntry("Circle",      &gamePadCheckReport, &(gamePadCheckReport.up), &(gamePadCheckReport.up.circle));
    formatReportEntry("Cross",       &gamePadCheckReport, &(gamePadCheckReport.up), &(gamePadCheckReport.up.cross));
    formatReportEntry("Square",      &gamePadCheckReport, &(gamePadCheckReport.up), &(gamePadCheckReport.up.square));
    formatReportEntry("Home",        &gamePadCheckReport, &(gamePadCheckReport.up), &(gamePadCheckReport.up.home));
    formatReportEntry("Hold",        &gamePadCheckReport, &(gamePadCheckReport.up), &(gamePadCheckReport.up.hold));
    formatReportEntry("Note",        &gamePadCheckReport, &(gamePadCheckReport.up), &(gamePadCheckReport.up.note));
    formatReportEntry("Screen",      &gamePadCheckReport, &(gamePadCheckReport.up), &(gamePadCheckReport.up.screen));
    formatReportEntry("VolUp",       &gamePadCheckReport, &(gamePadCheckReport.up), &(gamePadCheckReport.up.volUp));
    formatReportEntry("VolDown",     &gamePadCheckReport, &(gamePadCheckReport.up), &(gamePadCheckReport.up.volDown));
    formatReportEntry("WLAN",        &gamePadCheckReport, &(gamePadCheckReport.up), &(gamePadCheckReport.up.wlan));
    formatReportEntry("REMOTE_HOLD", &gamePadCheckReport, &(gamePadCheckReport.up), &(gamePadCheckReport.up.remoteHold));
    formatReportEntry("DISC(UMD)",   &gamePadCheckReport, &(gamePadCheckReport.up), &(gamePadCheckReport.up.disc));
    formatReportEntry("MemoryStick", &gamePadCheckReport, &(gamePadCheckReport.up), &(gamePadCheckReport.up.memoryStick));
    
    
    memcpy(&padOld, &pad, sizeof(padOld));
}