#ifndef PROJECTILES_H
#define PROJECTILES_H

typedef enum projectile_type {I, H} projectile_type;

typedef struct Projectile {
  int xpos;
  int ypos;
  int range;
  int speedx;
  int speedy;
  projectile_type type;
} Projectile;

//Projectile hostile_projectiles[10];
//Projectile isaac_projectiles[5];

#endif

void add_friendlies();

void add_enemies();

void move_projectiles();

void draw_projectiles();
