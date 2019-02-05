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
}

void create_rooms(Map *m, int level[]) {
  for (int i = 0; i < 9; i++) {
    if (!level[i]) {
      Room r = {.is_in_map = false};
      m->rooms[i] = r;
      continue;
    }

    
    Room r = {.cleared = 0, .is_in_map = 0};
    m->rooms[i] = r;
  }

  for (int i = 0; i < 9; i++) {
    m->rooms[i].doors[0] =  i > 2       && m->rooms[i-3].is_in_map ? 1 : 0; // up
    m->rooms[i].doors[1] = (i % 3) - 2  && m->rooms[i+1].is_in_map ? 1 : 0; // right
    m->rooms[i].doors[2] = i < 6        && m->rooms[i+3].is_in_map ? 1 : 0; // down
    m->rooms[i].doors[3] == i % 3       && m->rooms[i-1].is_in_map ? 1 : 0; // left
  }
}

