#include <Arduboy2.h>

#include "collisions.h"
#include "enemy.h"
#include "isaac.h"
#include "projectile.h"
#include "room.h"
#include "status.h"

Arduboy2 arduboy;

Enemy enemies[5];
int enemy_count = 0;
Projectile isaac_projectiles[4];
int isaac_projectile_count = 0;
Projectile hostile_projectiles[20];
int hostile_projectile_count = 0;

Isaac isaac = {40, 40, ISAAC_HEIGHT, ISAAC_WIDTH, 2, 2, isaac_bmp, 3};
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

  if (isaac.life == 0){
    arduboy.clear();
    arduboy.setCursor(20, 30);
    arduboy.print("I DED (RIP SAD)");
    arduboy.display();
    while (1){}
  }

  arduboy.display();

}
