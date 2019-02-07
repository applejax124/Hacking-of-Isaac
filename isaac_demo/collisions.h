#ifndef COLLISIONS_H
#define COLLISIONS_H

#include <Arduboy2.h>
#include "isaac.h"
#include "projectile.h"
#include "enemy.h"
#include "status.h"

void check_projectiles_to_enemies_collision(Arduboy2 * a, Enemy * enemies,
                                            int * num_enemies,
                                            Projectile * projectiles,
                                            int * num_projectiles);
void check_projectiles_to_isaac_collision(Arduboy2 * a, Isaac * isaac,
                                            Projectile * projectiles,
                                            int * num_projectiles);
void check_enemies_to_isaac_collision(Arduboy2 * a, Isaac * isaac,
                                            Enemy * enemies,
                                            int * num_enemies);

bool check_projectile_to_enemy_collision(Arduboy2 * a, Enemy * enemy,
                                         Projectile * projectile);
bool check_projectile_to_isaac_collision(Arduboy2 * a, Isaac * isaac,
                                         Projectile * projectile);
bool check_enemy_to_isaac_collision(Arduboy2 * a, Isaac * isaac,
                                         Enemy * enemy);

#endif
