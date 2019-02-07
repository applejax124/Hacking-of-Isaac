#include <Arduboy2.h>
#include "isaac.h"

#ifndef PROJECTILE_H
#define PROJECTILE_H

#define PROJECTILE_RANGE 12  //range for hostile projectiles
#define ISAAC_RANGE 12  //range for isaac projectiles

#define PROJECTILE_SPEEDX 3
#define PROJECTILE_SPEEDY 3

typedef enum projectile_type {I, H} projectile_type;

typedef struct Projectile {
  uint8_t xpos;
  uint8_t ypos;
  uint8_t range;
  uint8_t speedx;
  uint8_t speedy;
  projectile_type type;
  bool exists;
} Projectile;

void move_projectile(Projectile*, int*);
void draw_projectile(Arduboy2*, Projectile*);
void delete_projectile(Projectile * e, int * num_projectiles,
                        const int projectile_index);

#endif
