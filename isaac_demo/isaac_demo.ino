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


/*
 * 
 * SETUP FUNCTION
 * 
 */
void setup() {
  arduboy.begin();
  arduboy.setFrameRate(30);
}

/*
 * 
 * LOOP FUNCTION
 * 
 */
void loop() {
  if (!(arduboy.nextFrame())) {
    return;
  }
  arduboy.clear();

  move_isaac(&arduboy, &isaac);
  add_isaac_projectiles(&arduboy, &isaac, isaac_projectiles,
                        &isaac_projectile_count);
  check_use_door(&m, &isaac, STATUS_BAR_HEIGHT, enemy_count);

  for (int i = 0; i < 5; i++){
    if (enemies[i].exists){
      move_enemy(&enemies[i], &isaac);
    }
  }

  for (int i = 0; i < 4; i++){
    if (isaac_projectiles[i].exists){
      move_projectile(&isaac_projectiles[i]);
    }
  }

  for (int i = 0; i < 20; i++){
    if (hostile_projectiles[i].exists){
      move_projectile(&hostile_projectiles[i]);
    }
  }

  draw_room(&arduboy, &m.rooms[m.active_room], STATUS_BAR_HEIGHT);
  draw_status(&arduboy, &isaac, STATUS_BAR_HEIGHT);
  draw_isaac(&arduboy, &isaac);
  
  //draw enemies (if room not cleared)
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

  arduboy.setCursor(50, 20);
  arduboy.print(m.active_room);

  arduboy.display();

}
