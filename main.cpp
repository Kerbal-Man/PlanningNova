#include "raylib.h"
#include "methods.hpp"
#include <iostream>
#include <string>

int main(void){
    std::cout << "Special thanks to albert";
    //init everything
    //window init ALWAYS first
    int windowWidth  = 960;
    int windowHeight = 540;
    InitWindow(windowWidth, windowHeight, "Planning Nova");

    //varibles init down
    const bool debug = true;
    bool exitWindow = false;
    int menuReturnInt;
    //FPS Varibles
    int maxFPS = 60;
    int oldFPS = 0;
    int targetFPS = 0;
    int unfocusedFPS = 5;

    //Enums
    enum class currentMenu { Game = 0, Title = 1, Paused = 2 };
    enum class f3Menu      { OFF = 0, F3 = 1, FPSCHART = 2, F3FPSCHART = 3 };

    //init misc.
    Rectangle mainMenu = { 0.5 * windowWidth, 0.5 * windowHeight, .1 * windowWidth, .1 * windowHeight };
    Rectangle quitGame = { 0.5 * windowWidth, 0.1 * windowHeight, .3 * windowWidth, .1 * windowHeight };
    f3Menu currentF3Mode;
    currentMenu menu = currentMenu::Title;
    currentF3Mode = f3Menu::OFF;
    
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
        
        if (menu == currentMenu::Game)   { menuReturnInt = menuFrame(0, debug); }
        if (menu == currentMenu::Title)  { menuReturnInt = menuFrame(1, debug); }
        if (menu == currentMenu::Paused) { menuReturnInt = menuFrame(2, debug); }
        if (menuReturnInt == 0) { menu = currentMenu::Game; }
        if (menuReturnInt == 2) { menu = currentMenu::Paused; }
        if (menuReturnInt == 3) { exitWindow = true; }

        if (menu == currentMenu::Game) {
            //render game GUI
            SetMousePosition(GetWindowPosition().x, GetWindowPosition().y);
            DisableCursor();
        }

        if (menu == currentMenu::Title) {
            //render title menu
            DrawRectangleRec(quitGame, PINK);
            if (CheckCollisionPointRec(GetMousePosition(), quitGame) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
                exitWindow = true;
            }
            EnableCursor();
            ShowCursor();
        }

        if (menu == currentMenu::Paused) {
            //render paused menu
            EnableCursor();
            ShowCursor();
            DrawRectangleRec(mainMenu, GRAY);
            if (CheckCollisionPointRec(GetMousePosition(), mainMenu) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
                menu = currentMenu::Title;
            }
        }
        BeginDrawing();
        ClearBackground(BLACK);
        if (currentF3Mode == f3Menu::F3 || currentF3Mode == f3Menu::FPSCHART || currentF3Mode == f3Menu::F3FPSCHART || debug) { DrawFPS(10, 10); }

        //draw stuff in 2d 

        BeginMode3D(camera);
        DrawGrid(100, 1.0f);

        EndMode3D();

        EndDrawing();
    }

    CloseWindow();

    return 1;
}