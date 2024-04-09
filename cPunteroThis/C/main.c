#include <raylib.h>

//using byte = unsigned char;
//using dword = unsigned int;
//using sdword = ;

constexpr byte NUM_ENEMIES = 4;
constexpr int ENTITY_WIDTH = 64;
constexpr int ENTITY_HEIGHT = 48;
constexpr int SCR_WIDTH = 640;
constexpr int SCR_HEIGHT = 48;
constexpr char const WINDOW_TITLE[] ="Game";
constexpr int PLAYER_START_X = ENTITY_WIDTH/2;
constexpr int ENEMIES_START_X = SCR_WIDTH + (ENTITY_WIDTH/2);
constexpr int MOVE_STEP_X = ENTITY_WIDTH;
constexpr int ENEMY_VX = -MOVE_STEP_X;
constexpr Color PLAYER_COLOR = { 0, 121, 241, 255 };
constexpr Color ENEMY_COLOR = { 230, 41, 55, 255};

typedef struct {
    int x;
    int vx;
    Color color;
} Entity;

typedef struct {
    Entity player;
    bool playing;
    Entity enemies[NUM_ENEMIES];
} Game;

void game_init(Game* game){ //game es una dir de memoria = el puntero THIS
    InitWindow(SCR_WIDTH, SCR_HEIGHT, WINDOW_TITLE);

    *game = (Game){
        .player = (Entity){PLAYER_START_X, 0, PLAYER_COLOR},
        .playing = true,
        .enemies = {
            (Entity){ ENEMIES_START_X, ENEMY_VX, ENEMY_COLOR },
            (Entity){ ENEMIES_START_X, ENEMY_VX, ENEMY_COLOR },
            (Entity){ ENEMIES_START_X, ENEMY_VX, ENEMY_COLOR },
            (Entity){ ENEMIES_START_X, ENEMY_VX, ENEMY_COLOR }
        }
    };
}

void game_draw(Game const* this){
    BeginDrawing();
    ClearBackground(BLACK);

    DrawRectangle(this->player.x, 0, ENTITY_WIDTH, ENTITY_HEIGHT, this->player.color);
    EndDrawing();
}

void game_step(Game* this){
    this->playing = !IsKeyPressed(KEY_SPACE);
}

void game_destroy(){
    CloseWindow();
}

int main() {
    Game game;
    game_init(&game);

    //bool playing = true;    
    game_draw(&game);

    while ( game.playing ) {
        game_step(&game);
        game_draw(&game);
    }
    game_destroy();
    return 0;
}