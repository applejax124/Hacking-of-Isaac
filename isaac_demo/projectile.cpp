#include "projectile.h"

void move_projectile(Projectile* p){

  if (p->range == 0){   //delete projectile if current range is 0

    //TODO: remove projectile from room list (cami)

  } else {   //update projectile position

    p->range--;
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


