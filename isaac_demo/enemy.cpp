#include "enemy.h"

void draw_enemy(Arduboy2 arduboy, Enemy e){

  arduboy.drawSlowXYBitmap(e.xpos, e.ypos, e.bmp, e.width, e.height, WHITE);

};
