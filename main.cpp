#include "theIncluder.hpp"

int main(void){
    std::cout << "Special thanks to albert";
    //init everything
    //window init ALWAYS first
    int windowWidth  = 960;
    int windowHeight = 540;
    InitWindow(windowWidth, windowHeight, "Planning Nova");

    //window stats / flags
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    //varibles init down
    const bool debug = true;
    bool exitWindow = false;
    int menuReturnInt;

    //W O R L D
    
    game game;
    
    //FPS Varibles
    int maxFPS = 60;
    int oldFPS = 0;
    int targetFPS = 0;
    int unfocusedFPS = 5;
    
    //Enums
    enum class currentMenu { Game = 0, Title = 1, Paused = 2 };
    enum class f3Menu      { OFF = 0, F3 = 1, FPSCHART = 2, F3FPSCHART = 3 };

    //Buttons
    Rectangle mainMenu = { 0, 0, 0, 0,};
    Rectangle quitGame = { 0, 0, 0, 0,};
    Rectangle start    = { 0, 0, 0, 0,};
    
    //Textures / Images / Models / fonts
    Font defaultFont = LoadFont("C:\\Users\\noahg\\source\\repos\\PlanningNova\\x64\\Debug\\Textures\\Fonts\\minecraft_font.ttf");

    //init misc.
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
        
        windowHeight = GetScreenHeight();
        windowWidth = GetScreenWidth();
        mainMenu = { 0.1f * GetScreenWidth(), 0.5f  * GetScreenHeight(), 0.2f * GetScreenWidth(), 0.1f * GetScreenHeight() };
        quitGame = { 0.1f * GetScreenWidth(), 0.8f  * GetScreenHeight(), 0.2f * GetScreenWidth(), 0.1f * GetScreenHeight() };
        start    = { 0.1f * GetScreenWidth(), 0.05f * GetScreenHeight(), 0.2f * GetScreenWidth(), 0.1f * GetScreenHeight() };

        if (menu == currentMenu::Game) {
            //render game GUI
            SetMousePosition(GetWindowPosition().x, GetWindowPosition().y);
            DisableCursor();
        }

        if (menu == currentMenu::Title) {
            //render title menu
            DrawRectangleRec(start, GRAY);
            DrawTextEx(defaultFont, "Start", { start.x + 5, start.y }, 5 * GetScreenWidth() * GetScreenHeight() / 50000, 1, WHITE);
            DrawRectangleRec(quitGame, GRAY);
            if (CheckCollisionPointRec(GetMousePosition(), quitGame) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
                exitWindow = true;
            }
            if (CheckCollisionPointRec(GetMousePosition(), start) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
                menu = currentMenu::Game;
                std::cout << "ALBERT IS DUMB\n";
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
        if (menu == currentMenu::Game) { 
            DrawGrid(25, 1.0f); 
        }

        EndMode3D();

        EndDrawing();
    }

    CloseWindow();

    return 1;
}