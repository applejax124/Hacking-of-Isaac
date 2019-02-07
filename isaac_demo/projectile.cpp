#include "projectile.h"

void move_projectile(Projectile* p){

  if (p->range == 0){   //delete projectile if current range is 0

   //remove projectile from room list
   p->exists = 0;

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

void delete_projectile(Projectile * e, int * num_projectiles,
                        const int projectile_index) {
  e[projectile_index].exists = 0;
  *num_projectiles -= 1;
  for (int i = projectile_index; i < *num_projectiles; ++i) {
    e[i] = e[i+1];
  }
}
