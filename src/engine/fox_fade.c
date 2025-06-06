#include "global.h"

void Wipe_Horizontal(s32 frame) {
    Graphics_FillRectangle(&gMasterDisp, OTRGetRectDimensionFromLeftEdge(0), 0, OTRGetRectDimensionFromRightEdge(frame),
                           SCREEN_HEIGHT, 0, 0, 0, 255);
    Graphics_FillRectangle(&gMasterDisp, OTRGetRectDimensionFromLeftEdge(SCREEN_WIDTH - frame), 0,
                           OTRGetRectDimensionFromRightEdge(SCREEN_WIDTH), SCREEN_HEIGHT, 0, 0, 0, 255);
}

void Wipe_Vertical(s32 frame) {
    Graphics_FillRectangle(&gMasterDisp, OTRGetRectDimensionFromLeftEdge(0), 0,
                           OTRGetRectDimensionFromRightEdge(SCREEN_WIDTH), frame, 0, 0, 0, 255);
    Graphics_FillRectangle(&gMasterDisp, OTRGetRectDimensionFromLeftEdge(0), SCREEN_HEIGHT - frame,
                           OTRGetRectDimensionFromRightEdge(SCREEN_WIDTH), SCREEN_HEIGHT, 0, 0, 0, 255);
}

void Wipe_Circular(s32 frame) {
    s32 angle;

    RCP_SetupDL_12();
    Matrix_Push(&gGfxMatrix);
    Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -150.0f, MTXF_NEW);
    for (angle = 0; angle < MIN(360, frame * 15); angle += 15) {
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 0, 0, 0, MIN((frame - (angle / 15)) * 15, 255));
        Matrix_Push(&gGfxMatrix);
        Matrix_RotateZ(gGfxMatrix, angle * M_DTOR, MTXF_APPLY);
        Matrix_Scale(gGfxMatrix, 0.53f, 1.0f, 1.0f, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        gSPDisplayList(gMasterDisp++, D_Gfx_800D9688);
        Matrix_Pop(&gGfxMatrix);
    }
    Matrix_Pop(&gGfxMatrix);
}

void Wipe_Draw(WipeMode mode, s32 frame) {
    if (frame != 0) {
        switch (mode) {
            case WIPE_CIRCULAR:
                Wipe_Circular(frame);
                break;
            case WIPE_HORIZONTAL:
                Wipe_Horizontal(frame);
                break;
            case WIPE_VERTICAL:
                Wipe_Vertical(frame);
                break;
            default:
                PRINTF("そのような フェード は ない (%d)\n"); // There is no such fade
                break;
        }
    }
}
