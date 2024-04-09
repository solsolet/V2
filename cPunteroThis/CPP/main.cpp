#include <raylib.h>

int main() {
    auto playing {true};

    InitWindow(640, 48, "Game");

    while ( playing ) {
        BeginDrawing();
        playing = not IsKeyPressed(KEY_SPACE);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}