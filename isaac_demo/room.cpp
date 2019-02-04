#include "room.h"

int LEVEL = 1;

int level1[] = {0, 1, 0, 1, 1, 1, 0, 1, 0};
int level2[] = {1, 1, 1, 1, 0, 1, 1, 0, 1};
int level3[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};

// Draws all features of the room within the space specified.
void draw_room(Arduboy2 * arduboy, Room * r) {

  int door_width = 16;
  int door_thickness = 4;
  int top_margin = 10;

  if (r->doors[0]) {
    arduboy->fillRect(WIDTH/2 - door_width/2,
               top_margin + door_thickness, door_width, door_thickness, WHITE);
  }
  if (r->doors[1]) {
    arduboy->fillRect(WIDTH - door_thickness,
               (HEIGHT - top_margin)/2 - door_width/2 + top_margin, door_thickness, door_width, WHITE);
  }
  if (r->doors[2]) {
    arduboy->fillRect(WIDTH/2 - door_width/2,
               HEIGHT - door_thickness, door_width, door_thickness, WHITE);
  }
  if (r->doors[3]) {
    arduboy->fillRect(0,
               (HEIGHT - top_margin)/2 - door_width/2 + top_margin, door_thickness, door_width, WHITE);
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

