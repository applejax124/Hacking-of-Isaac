#include <enemy.h>
#include <obstacle.h>

#ifndef ROOM_H
#define ROOM_H

typedef struct room {
  Enemy enemies[];
  Obstacle obstacles[];
  int doors[4] = {0,0,0,0};
};

#endif
