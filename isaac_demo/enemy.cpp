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

void delete_enemy(Enemy * e, int * num_enemies,
                  const int enemy_index) {
  e[enemy_index].exists = 0;
  *num_enemies -= 1;
  for (int i = enemy_index; i < *num_enemies; ++i) {
    e[i] = e[i+1];
  }
}
