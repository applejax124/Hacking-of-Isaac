#include <Arduboy2.h>

#include "enemy.h"
#include "isaac.h"
#include "projectile.h"
#include "room.h"

Arduboy2 arduboy;

int tear_range = 0;
int tear_max_range = 12;
int tear_x = -1;
int tear_y = -1;
int tear_dx = 1;
int tear_dy = 0;


Enemy f1 = {20, 20, 6, 10, 1, 1, F, fly_bmp, 2};
Enemy p1 = {0, 0, 11, 9, 1, 1, P, pooter_bmp, 3};
Isaac isaac = {40, 40, 16, 16, 2, 2, isaac_bmp, 3};
Room r = {.doors = {1,0,0,0}, .cleared = 0 };
//Map m = create_map();

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

  draw_enemy(&arduboy, &f1);
  draw_enemy(&arduboy, &p1);
  draw_room(&arduboy, &r);
  draw_isaac(&arduboy, &isaac);
  
  move_isaac(&arduboy, &isaac);

  arduboy.display();
}


/*
 * Draw Projectiles
 */

void draw_projectiles() {

  // 
  
  // for now, only allowing 1 tear on screen at a time
  if (arduboy.pressed(B_BUTTON)) {
    tear_x = isaac.xpos + 8 + tear_dx;
    tear_y = isaac.ypos + 8 + tear_dy;
  }

  if (tear_x == -1) {
    return;
  }

  tear_range += 1;
  tear_x += 3*tear_dx;
  tear_y += 3*tear_dy;

  // check if tear is old/out of bounds
  if (!in_bounds(tear_x, tear_y, 0) || tear_range >= tear_max_range) {
    tear_range = 0;
    tear_x = -1;
    tear_y = -1;
  }

    arduboy.drawCircle(tear_x, tear_y, 1, WHITE);
}

bool in_bounds(int x, int y, int pad) {
  return x - pad > 0 and x + pad < WIDTH and y - pad > 0 and y + pad < WIDTH;
}
