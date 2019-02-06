#include <Arduboy2.h>

#include "enemy.h"
#include "isaac.h"
#include "projectile.h"
#include "room.h"
#include "status.h"

Arduboy2 arduboy;

int tear_range = 0;
int tear_max_range = 12;
int tear_x = -1;
int tear_y = -1;
int tear_dx = 1;
int tear_dy = 0;


Enemy f1 = {20, 20, 6, 10, 1, 1, F, fly_bmp, 2};
Enemy p1 = {30, 30, 11, 9, 1, 1, P, pooter_bmp, 3};
// TODO: the code currently assumes enemey lists will follow a pattern
//        of tracking size with a seperate integer.
int enemy_count = 0;

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

  draw_enemy(&arduboy, &f1);
  draw_enemy(&arduboy, &p1);
  draw_room(&arduboy, &m.rooms[m.active_room], STATUS_BAR_HEIGHT);
  draw_status(&arduboy, &isaac, STATUS_BAR_HEIGHT);
  draw_isaac(&arduboy, &isaac);
  
  move_isaac(&arduboy, &isaac);
  check_use_door(&m, &isaac, STATUS_BAR_HEIGHT, enemy_count);

  arduboy.setCursor(50, 20);
  arduboy.print(m.active_room);

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
