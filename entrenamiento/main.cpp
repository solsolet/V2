#include <raylib.h>

constexpr int WIDTH   { 800 };
constexpr int HEIGHT  { 600 };
constexpr auto* TITLE { "Celular" };
//dades mon
constexpr int ROW  { 8 };
constexpr int COL  { 7 };
constexpr int ROW_WIDTH  { WIDTH/ROW };
constexpr int COL_HEIGHT { HEIGHT/COL };
constexpr int M_CELLS  { ROW*COL }; //total cel·les mon

struct Mundo {
   bool state[M_CELLS]; //state 1 vivo, 0 muerta
};

void initMundo(Mundo mund){
   bool st{};
   for(int i=0; i<(M_CELLS);i++){
      mund.state[i] = st;
      st = !st;
   }
}


void draw() 
{
   Color color{};
   bool aux{};

   BeginDrawing();
   
   for(int i{}; i<ROW; i++){
      for(int j{}; j<COL; j++){ //el sistema de coordenades de raylib comença en 0,0 dalt a l'esquerra i va en diagonal cap avall
         color = aux ? RED : YELLOW;
         DrawRectangle(i*ROW_WIDTH,j*COL_HEIGHT,ROW_WIDTH,COL_HEIGHT, color);
         aux = !aux;
      }
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

