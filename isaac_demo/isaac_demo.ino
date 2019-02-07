#include <Arduboy2.h>

#include "collisions.h"
#include "enemy.h"
#include "isaac.h"
#include "projectile.h"
#include "room.h"
#include "status.h"

Arduboy2 arduboy;

Enemy f1 = {20, 20, 6, 10, 1, 1, F, fly_bmp, 2, 1};
Enemy p1 = {30, 30, 11, 9, 0, 0, P, pooter_bmp, 3, 1};
// TODO: the code currently assumes enemey lists will follow a pattern
//        of tracking size with a seperate integer.
Enemy enemies[5];
int enemy_count = 0;
Projectile isaac_projectiles[4];
int isaac_projectile_count = 0;
Projectile hostile_projectiles[20];
int hostile_projectile_count = 0;

Isaac isaac = {60, 40, ISAAC_HEIGHT, ISAAC_WIDTH, 2, 2, isaac_bmp, 3};
Map m = create_map();


void setup() {
  arduboy.begin();
  arduboy.setFrameRate(30);
  //instantiate enemies
  for (int i = 0; i < 5; i++){
    Enemy e;
    e.exists = 0;
    enemies[i] = e;
  }
  enemies[0] = p1;
  enemy_count = 1;

  //instantiate projectiles
  for (int i = 0; i < 4; i++){
    Projectile p;
    p.exists = 0;
    isaac_projectiles[i] = p;
  }
  for (int i = 0; i < 20; i++){
    Projectile p;
    p.exists = 0;
    hostile_projectiles[i] = p;
  }
}

void loop() {
  if (!(arduboy.nextFrame())) {
    return;
  }
  arduboy.clear();

  move_isaac(&arduboy, &isaac);
  add_isaac_projectiles(&arduboy, &isaac, isaac_projectiles,
                        &isaac_projectile_count);
  check_use_door(&m, &isaac, STATUS_BAR_HEIGHT, &enemy_count, enemies);

  for (int i = 0; i < 5; i++){
    if (enemies[i].exists){
      move_enemy(&enemies[i], &isaac);
    }
  }
  add_hostile_projectiles(&isaac, enemies, hostile_projectiles,
                        &hostile_projectile_count);

  for (int i = 0; i < 4; i++){
    if (isaac_projectiles[i].exists){
      move_projectile(&isaac_projectiles[i], &isaac_projectile_count);
    }
  }

  for (int i = 0; i < 20; i++){
    if (hostile_projectiles[i].exists){
      move_projectile(&hostile_projectiles[i], &hostile_projectile_count);
    }
  }

  // COLLISIONS
  check_projectiles_to_enemies_collision(&arduboy, enemies,
                                        &enemy_count,
                                        isaac_projectiles,
                                        &isaac_projectile_count);

  check_projectiles_to_isaac_collision(&arduboy, &isaac,
                                        hostile_projectiles,
                                        &hostile_projectile_count);

  check_enemies_to_isaac_collision(&arduboy, &isaac, enemies,
                                        &enemy_count);

  draw_room(&arduboy, &m.rooms[m.active_room], STATUS_BAR_HEIGHT);
  draw_status(&arduboy, &isaac, STATUS_BAR_HEIGHT);
  draw_isaac(&arduboy, &isaac);
  
  //draw enemies (if room not cleared)
  arduboy.setCursor(20, 30);
  arduboy.print(enemy_count);
  for (int i = 0; i < 5; i++){
    if (enemies[i].exists){
      draw_enemy(&arduboy, &enemies[i]);
    }
  }
  for (int i = 0; i < 4; i++){
    if (isaac_projectiles[i].exists){
      draw_projectile(&arduboy, &isaac_projectiles[i]);
    }
  }
  for (int i = 0; i < 20; i++){
    if (hostile_projectiles[i].exists){
      draw_projectile(&arduboy, &hostile_projectiles[i]);
    }
  }

  if(isaac.invincible) isaac.invincible -= 1;

  if (isaac.life == 0){
    arduboy.clear();
    arduboy.setCursor(20, 30);
    arduboy.print("I DED (RIP SAD)");
    arduboy.display();
    while (1){}
  }
  arduboy.setCursor(10,10);
  //arduboy.print(enemy_count);
  arduboy.print(enemies[0].xpos);
  arduboy.display();
}
