#include <raylib.h>

using byte = unsigned char;
using dword = unsigned int;
using sdword = int;

//class Entity
//public:
struct Entity {
    int vx;
    Color color;
};

constexpr byte      NUM_ENEMIES     { 4 };
constexpr int       ENTITY_WIDTH    { 64 };
constexpr int       ENTITY_HEIGHT   { 48 };
constexpr int       SCR_WIDTH       { 640 };
constexpr int       SCR_HEIGHT      { 48 };
constexpr char const WINDOW_TITLE[] { "Game" };
constexpr int       PLAYER_START_X  { ENTITY_WIDTH/2 };
constexpr int       ENEMIES_START_X { SCR_WIDTH + (ENTITY_WIDTH/2) };
constexpr int       MOVE_STEP_X     { ENTITY_WIDTH };
constexpr int       ENEMY_VX        { -MOVE_STEP_X };
constexpr Color     PLAYER_COLOR    { BLUE };
constexpr Color     ENEMY_COLOR     { YELLOW };

class Game {
    Entity player{ PLAYER_START_X, 0, PLAYER_COLOR };
    bool playing { true };
    Entity enemies [NUM_ENEMIES]{
        { ENEMIES_START_X, ENEMY_VX, ENEMY_COLOR },
        { ENEMIES_START_X, ENEMY_VX, ENEMY_COLOR },
        { ENEMIES_START_X, ENEMY_VX, ENEMY_COLOR },
        { ENEMIES_START_X, ENEMY_VX, ENEMY_COLOR }
    };
    explicit Game(){
        InitWindow(SCR_WIDTH, SCR_HEIGHT, WINDOW_TITLE);
    }
    void stop(){
        playing = not IsKeyPressed(KEY_SPACE);
    }
    void draw(){
        BeginDrawing();
        ClearBackground(BLACK);

        DrawRectangle(player.vx, 0, ENTITY_WIDTH, ENTITY_HEIGHT, PLAYER_COLOR);
        EndDrawing();
    }
    ~Game(){
        CloseWindow();
    }

};

int main() {
    Game game;

    game.draw();
    while ( game.playing ) {
        game.stop();
        game.draw();
    }
    return 0;
}