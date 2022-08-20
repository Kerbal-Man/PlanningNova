#include "raylib.h"

int main(void)
{
    //init everything
    //window init ALWAYS first
    InitWindow(800, 450, "Planning Nova");
    //varibles init down
    enum menu { Game, Title, Paused } currentMenu;
    //init misc.
    menu = Title;
    SetExitKey(KEY_PAUSE);

    while (!WindowShouldClose())
    {
        if (IsKeyReleased(KEY_ESCAPE)) {
            if (menu = Game) {
                menu = Paused;
            } else if (menu = Title) {
                CloseWindow();
            }else if (menu = Paused) {
                menu = Game;
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);

        DrawText("Menu = " + (char) menu, 10, 10, 50, WHITE);

        EndDrawing();
    }

    CloseWindow();

    return 1;
}