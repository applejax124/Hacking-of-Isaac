#ifndef PROJECTILES_H
#define PROJECTILES_H

#include <Arduboy2.h>
#include "isaac.h"
#include "room.h"
#include "enemy.h"

typedef enum projectile_type {I, H} projectile_type;

typedef struct Projectile {
  int xpos;
  int ypos;
  int range;
  int speedx;
  int speedy;
  projectile_type type;
} Projectile;

void add_isaac_projectiles(Arduboy2*, Isaac*, Room*);
void add_hostile_projectiles(Room*);
void move_projectile(Room*);
void draw_projectile(Arduboy2*, Room*);

#endif
