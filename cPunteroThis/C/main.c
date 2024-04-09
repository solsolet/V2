#include <raylib.h>

int main() {
    bool playing {true};

    InitWindow(640, 48, "Game");

    while ( playing ) {
        BeginDrawing();
        playing = !IsKeyPressed(KEY_SPACE);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}