#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct BoolReport {
    bool select;
    bool start;
    bool up;
    bool right;
    bool down;
    bool left;
    bool lTrigger;
    bool rTrigger;
    bool triangel;
    bool circle;
    bool cross;
    bool square;
    bool home;
    bool hold;
    bool note;
    bool screen;
    bool volUp;
    bool volDown;
    bool wlan;
    bool remoteHold;
    bool disc;
    bool memoryStick;
};

typedef struct {
    struct BoolReport down;
    struct BoolReport up;
    struct BoolReport downActive;
    struct BoolReport upActive;

    unsigned char min_analogX;
    unsigned char centerAvg_analogX;
    unsigned char max_analogX;
    unsigned char min_analgoY;
    unsigned char centerAvg_analogY;
    unsigned char max_analogY;
} GamePadCheckReport;

void gamePadCheck_init();
void gamePadCheck_cycle();