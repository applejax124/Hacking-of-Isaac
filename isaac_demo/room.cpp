#include "room.h"

int LEVEL = 1;

int level1[] = {0, 1, 0, 1, 1, 1, 0, 1, 0};
int level2[] = {1, 1, 1, 1, 0, 1, 1, 0, 1};
int level3[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};

// Draws all features of the room within the space specified.
void draw_room(Arduboy2 * arduboy, Room * r, Isaac *isaac, int top_margin) {
  if (r->doors[0]) {
    arduboy->fillRect(WIDTH/2 - DOOR_WIDTH/2,
                      top_margin + DOOR_THICKNESS,
                      DOOR_WIDTH, DOOR_THICKNESS, WHITE);
  }
  if (r->doors[1]) {
    arduboy->fillRect(WIDTH - DOOR_THICKNESS,
                      (HEIGHT - top_margin)/2 - DOOR_WIDTH/2 + top_margin,
                      DOOR_THICKNESS, DOOR_WIDTH, WHITE);
  }
  if (r->doors[2]) {
    arduboy->fillRect(WIDTH/2 - DOOR_WIDTH/2,
                      HEIGHT - DOOR_THICKNESS,
                      DOOR_WIDTH, DOOR_THICKNESS, WHITE);
  }
  if (r->doors[3]) {
    arduboy->fillRect(0, (HEIGHT - top_margin)/2 - DOOR_WIDTH/2 + top_margin,
                      DOOR_THICKNESS, DOOR_WIDTH, WHITE);
  }

  //draw enemies (if room not cleared)
  if (!r->cleared){
    for (int i = 0; i < 5; i++){
      if (r->enemies[i].exists){
        draw_enemy(arduboy, &r->enemies[i]);
      }
    }
  }

  //draw isaac
  draw_isaac(arduboy, isaac);

  //draw projectiles
  for (int i = 0; i < 4; i++){
    if (r->isaac_projectiles[i].exists){
      draw_projectile(arduboy, &r->isaac_projectiles[i]);
    }
  }

  for (int i = 0; i < 20; i++){
    if (r->hostile_projectiles[i].exists){
      draw_projectile(arduboy, &r->hostile_projectiles[i]);
    }
  }

}


Map create_map() {
  Map m;
  m.active_room = 1;
  if (LEVEL == 1) {
    create_rooms(&m, level1);
  } else if (LEVEL == 2) {
    create_rooms(&m, level2);
  } else if (LEVEL == 3) {
    create_rooms(&m, level3);
  }
  return m;
}

void create_rooms(Map *m, int level[]) {
  for (int i = 0; i < 9; i++) {
    if (!level[i]) {
      Room r;
      r.is_in_map = false;
      m->rooms[i] = r;
      continue;
    }

    Room r;
    r.cleared = 0;
    r.is_in_map = true;
    m->rooms[i] = r;
  }

  for (int i = 0; i < 9; i++) {
    m->rooms[i].doors[0] =  i > 2       && m->rooms[i-3].is_in_map ? 1 : 0; // up
    m->rooms[i].doors[1] = (i % 3) - 2  && m->rooms[i+1].is_in_map ? 1 : 0; // right
    m->rooms[i].doors[2] = i < 6        && m->rooms[i+3].is_in_map ? 1 : 0; // down
    m->rooms[i].doors[3] = i % 3        && m->rooms[i-1].is_in_map ? 1 : 0; // left
  }

  //TODO: generate enemies for each room in the map

}

// TODO: The constants used mary the system to a 3x3 grid, should abstract.
// TODO: Isaac should have a built-in reset method.
void check_use_door(Map * m, Isaac * i, int top_margin, int num_enemies) {
  if ((m->rooms[m->active_room].doors[0]) &&
      (i->xpos + ISAAC_WIDTH > WIDTH/2 - DOOR_WIDTH/2) &&
      (i->xpos < WIDTH/2 + DOOR_WIDTH/2) &&
      (i->ypos < top_margin + DOOR_THICKNESS) &&
      (num_enemies < 1) &&
      (m->active_room > 2)) {
    m->active_room -= 3;
    update_isaac_position(i, i->xpos, HEIGHT-i->ypos - 2*DOOR_THICKNESS);
  }
  if ((m->rooms[m->active_room].doors[1]) &&
      (i->ypos + ISAAC_HEIGHT > HEIGHT/2 - DOOR_WIDTH/2 + top_margin/2) &&
      (i->ypos < HEIGHT/2 + DOOR_WIDTH/2 + top_margin/2) &&
      (i->xpos + ISAAC_WIDTH > WIDTH - DOOR_THICKNESS) &&
      (num_enemies < 1) &&
      (m->active_room < 8)) {
    m->active_room += 1;
    update_isaac_position(i, WIDTH-i->xpos + DOOR_THICKNESS, i->ypos);
  }
  if ((m->rooms[m->active_room].doors[2]) &&
      (i->xpos + ISAAC_WIDTH > WIDTH/2 - DOOR_WIDTH/2) &&
      (i->xpos < WIDTH/2 + DOOR_WIDTH/2) &&
      (i->ypos + ISAAC_HEIGHT > HEIGHT - DOOR_THICKNESS) &&
      (num_enemies < 1) &&
      (m->active_room < 6)) {
    m->active_room += 3;
    update_isaac_position(i, i->xpos, HEIGHT-i->ypos + DOOR_THICKNESS);
  }
  if ((m->rooms[m->active_room].doors[3]) &&
      (i->ypos + ISAAC_HEIGHT > HEIGHT/2 - DOOR_WIDTH/2 + top_margin/2) &&
      (i->ypos < HEIGHT/2 + DOOR_WIDTH/2 + top_margin/2) &&
      (i->xpos < DOOR_THICKNESS) &&
      (num_enemies < 1) &&
      (m->active_room > 0)) {
    m->active_room -= 1;
    update_isaac_position(i, WIDTH-i->xpos - 4*DOOR_THICKNESS, i->ypos);
  }
}

void add_isaac_projectiles(Arduboy2 *arduboy, Isaac *isaac, Room *room){

  if (arduboy->pressed(B_BUTTON && room->n_isaac_projectiles < 4)) {

    room->n_isaac_projectiles++; //increment the number of isaac projectiles in the room
    for (int i = 0; i < 4; i++){

      if (!room->isaac_projectiles[i].exists){

        //create a new isaac projectile with all the current information
        int xspeed, yspeed;
        if (isaac->speedx == 0) {
          xspeed = 0;
        } else {
          xspeed = isaac->speedx < 0 ? -1 * PROJECTILE_SPEEDX : PROJECTILE_SPEEDX;
        }

        if (isaac->speedy == 0) {
          yspeed = 0;
        } else {
          yspeed = isaac->speedy < 0 ? -1 * PROJECTILE_SPEEDY : PROJECTILE_SPEEDY;
        }

        Projectile p = {isaac->xpos, isaac->ypos, ISAAC_RANGE, xspeed, yspeed, I, 1};
        room->isaac_projectiles[i] = p;

      }
    }

  }
}

void add_hostile_projectiles(Room *room, Isaac *isaac){

  for (int i = 0; i < 5; i++){
    if (room->enemies[i].type == P){   //only if the current enemy is a pooter

      //check if isaac is within range of a pooter dart and max projectiles note reached
      int xdiff = isaac->xpos - room->enemies[i].xpos;
      int ydiff = isaac->ypos - room->enemies[i].ypos;
      if (xdiff <= PROJECTILE_RANGE || ydiff <= PROJECTILE_RANGE && room->n_hostile_projectiles < 20){

        room->n_hostile_projectiles++; //increment the number of hostile projectiles in the room
        for (int j = 0; j < 20; j++){

          if (!room->hostile_projectiles[j].exists){

            //create a new hostile projectile with all the current information
            int xspeed = xdiff < 0 ? -1 * PROJECTILE_SPEEDX : PROJECTILE_SPEEDX;
            int yspeed = ydiff < 0 ? -1 * PROJECTILE_SPEEDY : PROJECTILE_SPEEDY;
            Projectile p = {room->enemies[j].xpos, room->enemies[j].ypos, PROJECTILE_RANGE, xspeed, yspeed, H, 1};
            room->isaac_projectiles[i] = p;
          }

        }

      }

    }
  }

}

//update the location of each of the elements in the room
void update_room(Arduboy2 *arduboy, Isaac *isaac, Room *room){

  //update isaac's position based on button presses
  move_isaac(arduboy, isaac);

  //update the position for each of the enemies in the room
  for (int i = 0; i < 5; i++){
    if (room->enemies[i].exists){
      move_enemy(&room->enemies[i], isaac);
    }
  }

  //update the positions of the projectiles in the room
  for (int i = 0; i < 4; i++){
    if (room->isaac_projectiles[i].exists){
      move_projectile(&room->isaac_projectiles[i]);
    }
  }

  for (int i = 0; i < 20; i++){
    if (room->hostile_projectiles[i].exists){
      move_projectile(&room->hostile_projectiles[i]);
    }
  }

}

//TODO: add enemies to each room in the map
void add_enemies(Map*){

}

