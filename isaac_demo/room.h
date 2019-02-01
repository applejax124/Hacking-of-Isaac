#ifndef ROOM_H
#define ROOM_H

#include "Arduboy2.h"

#define ROOM_DOOR_WIDTH 16
#define ROOM_DOOR_THICKNESS 4

struct Room {
  // Enemies[MAX_ENEMIES];
  // Obstacles[MAX_OBSTACLES];
  int doors[4] = {0,0,0,0}; // 4 positions: top, right, bottom, left
};

void draw_room(Arduboy2 * a, Room * r, int top_margin);

#endif
