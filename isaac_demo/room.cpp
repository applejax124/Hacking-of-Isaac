#include "room.h"

#include "isaac.h"

int LEVEL = 1;

int level1[] = {0, 1, 0, 1, 1, 1, 0, 1, 0};
int level2[] = {1, 1, 1, 1, 0, 1, 1, 0, 1};
int level3[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};

// Draws all features of the room within the space specified.
void draw_room(Arduboy2 * arduboy, Room * r, int top_margin) {
  if (r->doors[0]) {
    arduboy->fillRect(WIDTH/2 - DOOR_WIDTH/2,
               top_margin + DOOR_THICKNESS, DOOR_WIDTH, DOOR_THICKNESS, WHITE);
  }
  if (r->doors[1]) {
    arduboy->fillRect(WIDTH - DOOR_THICKNESS,
               (HEIGHT - top_margin)/2 - DOOR_WIDTH/2 + top_margin, DOOR_THICKNESS, DOOR_WIDTH, WHITE);
  }
  if (r->doors[2]) {
    arduboy->fillRect(WIDTH/2 - DOOR_WIDTH/2,
               HEIGHT - DOOR_THICKNESS, DOOR_WIDTH, DOOR_THICKNESS, WHITE);
  }
  if (r->doors[3]) {
    arduboy->fillRect(0,
               (HEIGHT - top_margin)/2 - DOOR_WIDTH/2 + top_margin, DOOR_THICKNESS, DOOR_WIDTH, WHITE);
  }
}


Map create_map() {
  Map *m;
  if (LEVEL == 1) {
    create_rooms(m, level1);
  } else if (LEVEL == 2) {
    create_rooms(m, level2);
  } else if (LEVEL == 3) {
    create_rooms(m, level3);
  }
}

void create_rooms(Map *m, int level[]) {
  for (int i = 0; i < 9; i++) {
    if (!level[i]) {
      //Room r = {.is_in_map = false};
      Room r;
      r.is_in_map = false;
      m->rooms[i] = r;
      continue;
    }

    //Room r = {.cleared = 0, .is_in_map = 0};
    Room r;
    r.cleared = 0;
    r.is_in_map = false;
    m->rooms[i] = r;
  }

  for (int i = 0; i < 9; i++) {
    m->rooms[i].doors[0] =  i > 2       && m->rooms[i-3].is_in_map ? 1 : 0; // up
    m->rooms[i].doors[1] = (i % 3) - 2  && m->rooms[i+1].is_in_map ? 1 : 0; // right
    m->rooms[i].doors[2] = i < 6        && m->rooms[i+3].is_in_map ? 1 : 0; // down
    m->rooms[i].doors[3] == i % 3       && m->rooms[i-1].is_in_map ? 1 : 0; // left
  }
}


// TODO: The constatnts used mary the system to a 3x3 grid, should abstract.
// TODO: Isaac should have a built-in reset method.
// TODO: Increase door tolerances to account for Isaac's width.
void check_use_door(Map * m, Isaac * i, int top_margin, int num_enemies) {
  if ((m->rooms[m->active_room].doors[0]) &&
      (i->xpos > WIDTH/2 - DOOR_WIDTH/2) && 
      (i->xpos < WIDTH/2 + DOOR_WIDTH/2) &&
      (i->ypos < top_margin + DOOR_THICKNESS) &&
      (num_enemies < 1) &&
      (m->active_room > 2)) {
    m->active_room -= 3;
    i->xpos = 40;
    i->ypos = 40;
  }
  if ((m->rooms[m->active_room].doors[1]) &&
      (i->ypos > HEIGHT/2 - DOOR_WIDTH/2 + top_margin/2) && 
      (i->ypos < HEIGHT/2 + DOOR_WIDTH/2 + top_margin/2) &&
      (i->xpos > WIDTH - DOOR_THICKNESS) &&
      (num_enemies < 1) &&
      (m->active_room < 8)) {
    m->active_room += 1;
    i->xpos = 40;
    i->ypos = 40;
  }
  if ((m->rooms[m->active_room].doors[2]) &&
      (i->xpos > WIDTH/2 - DOOR_WIDTH/2) && 
      (i->xpos < WIDTH/2 + DOOR_WIDTH/2) &&
      (i->ypos > HEIGHT - DOOR_THICKNESS) &&
      (num_enemies < 1) &&
      (m->active_room < 6)) {
    m->active_room += 3;
    i->xpos = 40;
    i->ypos = 40;
  }
  if ((m->rooms[m->active_room].doors[3]) &&
      (i->ypos > HEIGHT/2 - DOOR_WIDTH/2 + top_margin/2) && 
      (i->ypos < HEIGHT/2 + DOOR_WIDTH/2 + top_margin/2) &&
      (i->xpos < WIDTH + DOOR_THICKNESS) &&
      (num_enemies < 1) && 
      (m->active_room > 0)) {
    m->active_room -= 1;
    i->xpos = 40;
    i->ypos = 40;
  }
}
