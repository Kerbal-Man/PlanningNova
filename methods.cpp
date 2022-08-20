#include "methods.h"
#include "raylib.h"
#include <iostream>

int menuFrame(int menu, bool debug) {

    if (debug) {
        if (menu == 0) { DrawText("Menu = Game",   100, 10, 20, WHITE); }
        if (menu == 1) { DrawText("Menu = Title",  100, 30, 20, WHITE); }
        if (menu == 2) { DrawText("Menu = Paused", 100, 50, 20, WHITE); }
    }
    
    if (IsKeyReleased(KEY_ESCAPE)) {
        std::cout << "window Closed";
        
    }
    
    
    return 0;
}