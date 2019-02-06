#include "collisions.h"

#include "Arduboy2.h"
#include "isaac.h"
#include "projectile.h"
#include "enemy.h"
#include "status.h"

void check_projectiles_to_enemies_collision(Arduboy2 * a,
                                            Enemy * enemies, int * num_enemies,
                                            Projectile * projectiles,
                                            int * num_projectiles) {
  for (int e_index = 0; e_index < (*num_enemies); e_index++) {
    for (int p_index = 0; p_index < (*num_projectiles); p_index++) {
      if (check_projectile_to_enemy_collision(a, &enemies[e_index], 
                                            &projectiles[p_index])) {
        delete_projectile(projectiles, num_projectiles, p_index);
        enemies[e_index].life -= 1;
        if (enemies[e_index].life < 1) {
          delete_enemy(enemies, num_enemies, e_index);
        }
      }
    }
  }
}

void check_projectiles_to_isaac_collision(Arduboy2 * a,
                                            Isaac * isaac,
                                            Projectile * projectiles,
                                            int * num_projectiles) {
  for (int p_index = 0; p_index < (*num_projectiles); p_index++) {
    if (check_projectile_to_isaac_collision(a, isaac, 
                                          &projectiles[p_index])) {
      delete_projectile(projectiles, num_projectiles, p_index);
      isaac->life -= 1;
    }
  }
}

void check_enemies_to_isaac_collision(Arduboy2 * a,
                                      Isaac * isaac,
                                      Enemy * enemies,
                                      int * num_enemies) {
  for (int p_index = 0; p_index < (*num_enemies); p_index++) {
    if (check_enemy_to_isaac_collision(a, isaac, 
                                          &enemies[p_index])) {
      isaac->life -= 1;
    }
  }
}

bool check_projectile_to_enemy_collision(Arduboy2 * a,
                                         Enemy * enemy,
                                         Projectile * projectile) {
  return a->collide(Rect{enemy->xpos, enemy->ypos,
                          enemy->xpos+enemy->width,
                          enemy->ypos-enemy->height},
                        Rect{projectile->xpos, projectile->ypos,
                          projectile->xpos+projectile->width,
                          projectile->ypos-projectile->height});
}

bool check_projectile_to_isaac_collision(Arduboy2 * a,
                                         Isaac * isaac,
                                         Projectile * projectile) {
  return a->collide(Rect{isaac->xpos, isaac->ypos,
                          isaac->xpos+isaac->width,
                          isaac->ypos-isaac->height},
                        Rect{projectile->xpos, projectile->ypos,
                          projectile->xpos+projectile->width,
                          projectile->ypos-projectile->height});
}

bool check_enemy_to_isaac_collision(Arduboy2 * a,
                                    Isaac * isaac,
                                    Enemy * enemy) {
  return a->collide(Rect{isaac->xpos, isaac->ypos,
                          isaac->xpos+isaac->width,
                          isaac->ypos-isaac->height},
                        Rect{enemy->xpos, enemy->ypos,
                          enemy->xpos+enemy->width,
                          enemy->ypos-enemy->height});
}
