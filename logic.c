#include "logic.h"
#include "physics.h"

void initializeAppState(AppState* appState) {
    appState->player.point.x = 120;
    appState->player.point.y = 143;
    appState->player.point.isFalling = 0;
    appState->player.point.hvelocity = 0;
    appState->player.point.vvelocity = 0;
    appState->player.point.vaccel = 0;
    appState->player.point.haccel = 0;
}

// TA-TODO: Add any process functions for sub-elements of your app here.
// For example, for a snake game, you could have a processSnake function
// or a createRandomFood function or a processFoods function.
//
// e.g.:
// static Snake processSnake(Snake* currentSnake);
// static void generateRandomFoods(AppState* currentAppState, AppState* nextAppState);

// This function processes your current app state and returns the new (i.e. next)
// state of your application.
AppState processAppState(AppState *currentAppState, u32 keysPressedBefore, u32 keysPressedNow) {
    /* TA-TODO: Do all of your app processing here. This function gets called
     * every frame.
     *
     * To check for key presses, use the KEY_JUST_PRESSED macro for cases where
     * you want to detect each key press once, or the KEY_DOWN macro for checking
     * if a button is still down.
     *
     * To count time, suppose that the GameBoy runs at a fixed FPS (60fps) and
     * that VBlank is processed once per frame. Use the vBlankCounter variable
     * and the modulus % operator to do things once every (n) frames. Note that
     * you want to process button every frame regardless (otherwise you will
     * miss inputs.)
     *
     * Do not do any drawing here.
     *
     * TA-TODO: VERY IMPORTANT! READ THIS PART.
     * You need to perform all calculations on the currentAppState passed to you,
     * and perform all state updates on the nextAppState state which we define below
     * and return at the end of the function. YOU SHOULD NOT MODIFY THE CURRENTSTATE.
     * Modifying the currentAppState will mean the undraw function will not be able
     * to undraw it later.
     */

    AppState nextAppState = *currentAppState;

    if (KEY_JUST_PRESSED(BUTTON_A, keysPressedNow, keysPressedBefore)) {
        jump(&(nextAppState.player));
    }
    if (KEY_DOWN(BUTTON_RIGHT, keysPressedNow)) {
        nextAppState.player.point.haccel = 5;
    } else if (KEY_DOWN(BUTTON_LEFT, keysPressedNow)) {
        nextAppState.player.point.haccel = -5;
    } else if (nextAppState.player.point.hvelocity > 0){
        nextAppState.player.point.haccel = -5;
    } else if (nextAppState.player.point.hvelocity < 0) {
        nextAppState.player.point.haccel = 5;
    } else {
        nextAppState.player.point.haccel = 0;
    }
    moveVectorY(&nextAppState.player.point);
    moveVectorX(&nextAppState.player.point);
    return nextAppState;
}
