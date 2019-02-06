#include "room.h"

int LEVEL = 1;

int level1[] = {0, 1, 0, 1, 1, 1, 0, 1, 0};
int level2[] = {1, 1, 1, 1, 0, 1, 1, 0, 1};
int level3[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};

// Draws all features of the room within the space specified.
void draw_room(Arduboy2 * arduboy, Room * r, int top_margin) {
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

  //TODO: draw enemies (if not cleared) (cami)

  //TODO: draw isaac (cami)

  //TODO: draw projectiles in the room (cami)

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

//update the location of each of the elements in the room
void update_room(Arduboy2 *arduboy, Isaac *isaac, Room *room){

  //update isaac's position based on button presses
  move_isaac(arduboy, isaac);

  //update the position for each of the enemies in the room
  for (int i = 0; i < 5; i++){
    //TODO: check if this is the correct value (cami)
    if (room->enemies[i] != NULL){
      move_enemy(room->enemies[i], isaac);
    }
  }

  //update the positions of the projectiles in the room
  for (int i = 0; i < 4; i++){
    //TODO: check if this is the correct value (cami)
    if (room->isaac_projectiles[i] != NULL){
      move_projectile(room->isaac_projectiles[i]);
    }
  }

  for (int i = 0; i < 20; i++){
    //TODO: check if this is the correct value (cami)
    if (room->hostile_projectiles[i] != NULL){
      move_projectile(room->hostile_projectiles[i]);
    }
  }

}
