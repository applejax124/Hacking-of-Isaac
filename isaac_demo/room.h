#ifndef ROOM_H
#define ROOM_H

#include "Arduboy2.h"
#include "isaac.h"

#define DOOR_WIDTH 16
#define DOOR_THICKNESS 4

typedef struct Room {
  //Enemy enemies[];
  //Obstacle obstacles[];
  int doors[4];
  bool cleared;
  bool is_in_map;
} Room;

typedef struct Map {
  bool cleared;
  Room rooms[9];
  int active_room;
} Map;

void create_rooms(Map *m, int level[]);
void draw_room(Arduboy2 * arduboy, Room * r, int top_margin);
void check_use_door(Map * m, Isaac * i, int top_margin, int num_enemies);
Map create_map();

#endif
