#include "raylib.h"
#include "methods.hpp"
#include <iostream>

int main(void)
{
    //init everything
    //window init ALWAYS first
    InitWindow(960, 540, "Planning Nova");
    //varibles init down
    const bool debug = true;
    bool exitWindow = false;
    int maxFPS = 60;
    int oldFPS = 0;
    int targetFPS = 0;
    int unfocusedFPS = 5;
    enum currentMenu { Game = 0, Title = 1, Paused = 2 } menu;
    enum f3Menu      { OFF = 0, F3 = 1, FPSCHART = 2, F3FPSCHART = 3 } currentF3Mode;
    //init misc.
    menu = Title;
    currentF3Mode = OFF;
    SetExitKey(KEY_PAUSE);

    //draw da game
    while (!exitWindow) {
        if (!maxFPS == oldFPS                              ) { oldFPS = maxFPS;          SetTargetFPS(maxFPS);       targetFPS = maxFPS; }
        if (!IsWindowFocused() && targetFPS != unfocusedFPS) { targetFPS = unfocusedFPS; SetTargetFPS(unfocusedFPS);                     }
        if (IsWindowFocused() && targetFPS != maxFPS       ) { targetFPS = maxFPS;       SetTargetFPS(maxFPS);                           }
        if (IsKeyPressed(KEY_PAUSE) || WindowShouldClose()) exitWindow = true;
        if (menu == 0) { menuFrame(0, debug); }
        if (menu == 1) { menuFrame(1, debug); }
        if (menu == 2) { menuFrame(2, debug); }
        
        BeginDrawing();
        ClearBackground(BLACK);
        
        

        EndDrawing();
    }

    CloseWindow();

    return 1;
}