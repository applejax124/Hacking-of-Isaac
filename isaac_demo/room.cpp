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
  
  /*
  for (int i = 0; i < 9; i++) {
    //Room curr_room = {.doors = {1,0,0,0}, .cleared = 0};
    if (LEVEL == 1) {
    } else if (LEVEL == 2) {
      
    }  else if (LEVEL == 3) {
      
    }
    //m.rooms[i] = curr_room;
  }*/
}

void create_rooms(Map *m, int level[]) {
  for (int i = 0; i < 9; i++) { 
    int is_up = i < 3 ? 1 : 0;
    int is_right = (i % 3) - 2 == 0 ? 1 : 0;
    int is_down = i > 5 ? 1 : 0;
    int is_left = i % 3 == 0 ? 1 : 0;
    
    Room r = {.doors = {is_up, is_right, is_down, is_left}, .cleared = 0};
    m->rooms[i] = r;
  }
}

void check_use_door(Map * m, Isaac * i, int top_margin, int num_enemies) {
  if ((m->rooms[m->active_room].doors[0]) &&
      (i->xpos > WIDTH/2 - DOOR_WIDTH/2) && 
      (i->xpos < WIDTH/2 + DOOR_WIDTH/2) &&
      (i->ypos < top_margin + DOOR_THICKNESS) &&
      (num_enemies < 1)) {
    m->active_room -= 3;
  }
  if ((m->rooms[m->active_room].doors[1]) &&
      (i->ypos > HEIGHT/2 - DOOR_WIDTH/2 + top_margin/2) && 
      (i->ypos < HEIGHT/2 + DOOR_WIDTH/2 + top_margin/2) &&
      (i->xpos > WIDTH - DOOR_THICKNESS) &&
      (num_enemies < 1)) {
    m->active_room += 1;
  }
  if ((m->rooms[m->active_room].doors[2]) &&
      (i->xpos > WIDTH/2 - DOOR_WIDTH/2) && 
      (i->xpos < WIDTH/2 + DOOR_WIDTH/2) &&
      (i->ypos > HEIGHT - DOOR_THICKNESS) &&
      (num_enemies < 1)) {
    m->active_room += 3;
  }
  if ((m->rooms[m->active_room].doors[3]) &&
      (i->ypos > HEIGHT/2 - DOOR_WIDTH/2 + top_margin/2) && 
      (i->ypos < HEIGHT/2 + DOOR_WIDTH/2 + top_margin/2) &&
      (i->xpos < WIDTH + DOOR_THICKNESS) &&
      (num_enemies < 1)) {
    m->active_room -= 1;
  }
}
