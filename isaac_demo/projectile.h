#ifndef PROJECTILES_H
#define PROJECTILES_H

#include <Arduboy2.h>
#include "isaac.h"
#include "room.h"

#define PROJECTILE_RANGE 12  //range for hostile projectiles
#define ISAAC_RANGE 12  //range for isaac projectiles

#define PROJECTILE_SPEEDX 3
#define PROJECTILE_SPEEDY 3

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
void add_hostile_projectiles(Room*, Isaac*);
void move_projectile(Projectile*);
void draw_projectile(Arduboy2*, Projectile*);

#endif
