#include "enemy.h"

void draw_enemy(Arduboy2 * arduboy, Enemy * e){

  arduboy->drawSlowXYBitmap(e->xpos, e->ypos, e->bmp, e->width, e->height, WHITE);

}

void move_enemy(Enemy *enemy, Isaac *isaac){

  int xdiff = isaac->xpos - enemy->xpos;
  int ydiff = isaac->ypos - enemy->ypos;

  //update enemy position based on isaac's location
  enemy->xpos += xdiff > 0 ? enemy->speedx : -1 * enemy->speedx;
  enemy->ypos += ydiff > 0 ? enemy->speedy : -1 * enemy->speedy;

}