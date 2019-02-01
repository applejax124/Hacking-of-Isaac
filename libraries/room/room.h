#include <enemy.h>
#include <obstacle.h>

#ifndef ROOM_H
#define ROOM_H

typedef struct room {
  Enemy enemies[];
  Obstacle obstacles[];
  int doors[];
};

#endif
