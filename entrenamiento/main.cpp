#include <raylib.h>

constexpr int WIDTH   { 800 };
constexpr int HEIGHT  { 600 };
constexpr auto* TITLE { "Celular" };
//datos del mundo
constexpr int COL  { 8 };
constexpr int ROW  { 6 };

struct Mundo {
   bool estado[COL*ROW]; //estado 1 vivo, 0 muerta
};

void initMundo(Mundo mund){
   bool est{};
   for(int i=0; i<(COL*ROW);i++){
      mund.estado[i] = est;
      est = !est;
   }
}


void draw() 
{
   Color color{};
   bool aux{};
   BeginDrawing();
   //DrawRectangle(0,0,16,12,WHITE);
   for(int i{}; i<ROW; i++)
      for(int j{}; j<COL; j++){
         color = aux ? RED : YELLOW;
         DrawRectangle(i*(WIDTH/ROW),j*(HEIGHT/COL),WIDTH/ROW,HEIGHT/COL, color);
         aux = !aux;
      }
   EndDrawing();
}

int main() 
{
   Mundo m;
   InitWindow(WIDTH, HEIGHT, TITLE);
   initMundo(m);

   while ( !WindowShouldClose() ) {
      draw();
   }

   CloseWindow();
   return 0;
}

