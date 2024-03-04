#include <cstdlib>
#include <gamemanager.hpp>

constexpr uint16_t      SCR_WIDTH  { 800 };
constexpr uint16_t      SCR_HEIGHT { 600 };
constexpr std::string   GAME_TITLE { "My Game" };

int main() {
   GameManager game{SCR_WIDTH, SCR_HEIGHT, GAME_TITLE};
   game.run();
}