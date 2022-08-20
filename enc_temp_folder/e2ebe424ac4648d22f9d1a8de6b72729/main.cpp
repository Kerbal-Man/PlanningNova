#include "raylib.h"
#include "methods.h"
#include <iostream>
static bool closeWindow;

int main(void)
{
    //init everything
    //window init ALWAYS first
    InitWindow(960, 540, "Planning Nova");
    //varibles init down
    const bool debug = true;
    closeWindow = false;
    int maxFPS = 60;
    int oldFPS = 0;
    int targetFPS = 0;
    int unfocusedFPS = 5;
    enum currentMenu { Game = 0, Title = 1, Paused = 2 } menu;
    //init misc.
    
    menu = Title;
    SetExitKey(KEY_PAUSE);

    while (CloseWindow) {
        if (!maxFPS == oldFPS                              ) { oldFPS = maxFPS;          SetTargetFPS(maxFPS);       targetFPS = maxFPS; }
        if (!IsWindowFocused() && targetFPS != unfocusedFPS) { targetFPS = unfocusedFPS; SetTargetFPS(unfocusedFPS);                     }
        if (IsWindowFocused() && targetFPS != maxFPS       ) { targetFPS = maxFPS;       SetTargetFPS(maxFPS);                           }
        if (WindowShouldClose()) { closeWindow = true; }
        if (menu == 0) { menuFrame(0, debug); }
        if (menu == 1) { menuFrame(1, debug); }
        if (menu == 2) { menuFrame(2, debug); }
        



        BeginDrawing();
        ClearBackground(BLACK);
        
        DrawFPS(5, 5);

        EndDrawing();
    }

    CloseWindow();

    return 1;
}