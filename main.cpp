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

    //FPS Varibles
    int maxFPS = 60;
    int oldFPS = 0;
    int targetFPS = 0;
    int unfocusedFPS = 5;

    //Enums
    enum class currentMenu { Game = 0, Title = 1, Paused = 2 };
    enum class f3Menu      { OFF = 0, F3 = 1, FPSCHART = 2, F3FPSCHART = 3 };

    //init misc.
    f3Menu currentF3Mode;
    currentMenu menu;
    menu = currentMenu::Game;
    currentF3Mode = f3Menu::OFF;
    Rectangle quitToMainMenuButton; quitToMainMenuButton.x = 380; quitToMainMenuButton.y = 230; quitToMainMenuButton.width = 200; quitToMainMenuButton.height = 60;
    SetExitKey(KEY_PAUSE);

    //Camera Varibles
    Camera3D camera = { 0 };
    camera.position = { 0.0f, 1.0f, 10.0f };  // Camera position
    camera.target   = { 0.0f, 0.0f, 0.0f };    // Camera looking at point
    camera.up       = { 0.0f, 1.0f, 0.0f };    // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                       // Camera field-of-view
    camera.projection = CAMERA_PERSPECTIVE;    // Camera mode type
    SetCameraMode(camera, CAMERA_FIRST_PERSON);

    //draw da game
    while (!exitWindow) {
        //A WHOLE LOT OF LOGIC
        if (menu == currentMenu::Game) { UpdateCamera(&camera); }
        if (!maxFPS == oldFPS                              ) { oldFPS = maxFPS;          SetTargetFPS(maxFPS);       targetFPS = maxFPS; }
        if (!IsWindowFocused() && targetFPS != unfocusedFPS) { targetFPS = unfocusedFPS; SetTargetFPS(unfocusedFPS);                     }
        if (IsWindowFocused() && targetFPS != maxFPS       ) { targetFPS = maxFPS;       SetTargetFPS(maxFPS);                           }
        if (IsKeyPressed(KEY_PAUSE) || WindowShouldClose()) exitWindow = true;
        if (IsKeyPressed(KEY_ESCAPE)) {
            if (menu == currentMenu::Game)   { menu = currentMenu::Paused; std::cout << "Pause";    } else
            if (menu == currentMenu::Title)  { exitWindow = true;          std::cout << "END GAME"; } else
            if (menu == currentMenu::Paused) { menu = currentMenu::Game;   std::cout << "Resum";    }
        }
        if (menu == currentMenu::Game)   { menuFrame(0, debug); }
        if (menu == currentMenu::Title)  { menuFrame(1, debug); }
        if (menu == currentMenu::Paused) { menuFrame(2, debug); }
        
        BeginDrawing();
        ClearBackground(BLACK);
        if (currentF3Mode == f3Menu::F3 || currentF3Mode == f3Menu::FPSCHART || currentF3Mode == f3Menu::F3FPSCHART || debug) { DrawFPS(10, 10); }
        
        //draw stuff in 2d 
        if (menu == currentMenu::Paused) {
            //render paused menu
            EnableCursor();
            ShowCursor();
            DrawRectangle(quitToMainMenuButton.x, quitToMainMenuButton.y, quitToMainMenuButton.width, quitToMainMenuButton.height, RED);
            if (CheckCollisionPointRec(GetMousePosition(), quitToMainMenuButton) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                menu = currentMenu::Title;
            }
        } else {
            DisableCursor();
        }


        BeginMode3D(camera);
        DrawGrid(100, 1.0f);

        EndMode3D();

        EndDrawing();
    }

    CloseWindow();

    return 1;
}