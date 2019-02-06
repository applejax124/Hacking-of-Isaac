#include "projectile.h"

void add_isaac_projectiles(Arduboy2 *arduboy, Isaac *isaac, Room *room){

  if (arduboy->pressed(B_BUTTON && room->n_isaac_projectiles < 4)) {

    room->n_isaac_projectiles++; //increment the number of isaac projectiles in the room
    for (int i = 0; i < 4; i++){

      //TODO: figure out what the default value of this is (cami)
      if (room->isaac_projectiles[i] == NULL){

        //create a new isaac projectile with all the current information
        Projectile p = {isaac->xpos, isaac->ypos, I_RANGE, isaac->speedx, isaac->speedy, I};
        room->isaac_projectiles[i] = p;

      }
    }

  }
}

void add_hostile_projectiles(Room *room, Isaac *isaac){

  for (int i = 0; i < 5; i++){
    if (room->enemies[i]->type == P){   //only if the current enemy is a pooter

      //check if isaac is within range of a pooter dart and max projectiles note reached
      int xdiff = isaac->xpos - room->enemies[i]->xpos;
      int ydiff = isaac->ypos - room->enemies[i]->ypos
      if (xdiff <= H_RANGE || ydiff <= H_RANGE && room->n_add_hostile_projectiles < 20){

        room->n_hostile_projectiles++; //increment the number of hostile projectiles in the room
        for (int j = 0; j < 20; j++){

          //TODO: figure out what the default value of this is (cami)
          if (room->hostile_projectiles[j] == NULL){

            //create a new hostile projectile with all the current information
            int xspeed = xdiff < 0 ? -1 * PROJECTILE_SPEEDX : PROJECTILE_SPEEDX;
            int yspeed = ydiff < 0 ? -1 * PROJECTILE_SPEEDY : PROJECTILE_SPEEDY;
            Projectile p = {room->enemies[j]->xpos, room->enemies[j]->ypos, I_RANGE, xspeed, yspeed, H};
            room->isaac_projectiles[i] = p;
          }

        }

      }

    }
  }
  
}

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


