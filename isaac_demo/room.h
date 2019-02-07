#include <Arduboy2.h>
#include "isaac.h"
#include "status.h"
#include "enemy.h"
#include "projectile.h"

#ifndef ROOM_H
#define ROOM_H

#define DOOR_WIDTH 16
#define DOOR_THICKNESS 4

typedef struct Room {
  int n_enemies;
  int n_isaac_projectiles;
  int n_hostile_projectiles;
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
void update_room(Arduboy2*, Isaac*, Room*);
void add_isaac_projectiles(Arduboy2 *arduboy, Isaac *isaac,
                            Projectile * isaac_projectiles,
                            int * n_isaac_projectiles);
void add_hostile_projectiles(Isaac *isaac,
                             Projectile * hostile_projectiles,
                             int * n_hostile_projectiles);
void add_enemies(Map*);

#endif
