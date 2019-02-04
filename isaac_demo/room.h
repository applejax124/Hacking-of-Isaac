#include <Arduboy2.h>

#ifndef ROOM_H
#define ROOM_H

typedef struct Room {
  //Enemy enemies[];
  //Obstacle obstacles[];
  int doors[4];
} Room;

void draw_room(Arduboy2 * arduboy, Room * r);

#endif
