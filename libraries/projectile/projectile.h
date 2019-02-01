#ifndef PROJECTILES_H
#define PROJECTILES_H

enum projectile_type {F, E};

typedef struct Projectile {
  int xpos;
  int ypos;
  int range;
  int speedx;
  int speedy;
  projectile_type type;
} Projectile;

Projectile enemy_projectiles[];

Projectile isaac_projectiles[];

#endif
