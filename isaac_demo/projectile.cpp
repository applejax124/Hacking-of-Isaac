#include "projectile.h"

void move_projectile(Projectile* p, int * count){

  if (p->range == 0){   //delete projectile if current range is 0

    //remove projectile from room list
    p->exists = 0;
    *count -= 1;

  } else {   //update projectile position

    p->range -= 1;
    p->xpos += p->speedx;
    p->ypos += p->speedy;

  }

}

void draw_projectile(Arduboy2 *arduboy, Projectile* p){

  if (p->type == I){
    arduboy->drawCircle(p->xpos, p->ypos, 1, WHITE);
  } else if (p->type == H){
    arduboy->fillCircle(p->xpos, p->ypos, 1, WHITE);
  }

}
