#include <Arduboy2.h>

#include "isaac.h"
#include "memory.h"
#include "projectile.h"
#include "room.h"


Arduboy2 arduboy;

int isaac_x = 64;
int isaac_y = 31;
int isaac_size = 16;

int tear_range = 0;
int tear_max_range = 12;
int tear_x = -1;
int tear_y = -1;
int tear_dx = 1;
int tear_dy = 0;



// index of map to draw.
int active_room = 1;
// A sample room
Room test_room;
// All living Creeps

// Isaac, our intrepid protagonist.
Isaac isaac;


void setup() {
  arduboy.begin();
  arduboy.setFrameRate(30);

  // Initial isaac values.
  isaac.x_pos = 64;
  isaac.y_pos = 31;
  isaac.size = 16;

  test_room.doors[0] = 1;
  test_room.doors[1] = 1;
  test_room.doors[2] = 1;
  test_room.doors[3] = 1;
}

void loop() {
  // End game if the program is done drawing.
  if (!(arduboy.nextFrame())) {
    return;
  }
  arduboy.clear();

  // Draw information that will surround map
  //draw_window();
  // Draw room background + any obstacles and doors
  draw_room(&arduboy, &test_room, 10);
  // Move and draw all enemies
  //move_creeps();
  //draw_creeps();
  // redraw isaac
  //draw_isaac();
  draw_isaac(&isaac, &arduboy);
  // reposition and draw all projectiles
  //move_projectiles();
  //draw_projectiles();

  // this is a great way to debug lmao
  arduboy.setCursor(10, 10);
  //arduboy.print(tear_x);
  arduboy.display();
}

void draw_isaac() {
  // move isaac according to d-pad input
  if (arduboy.pressed(RIGHT_BUTTON) && isaac_x < WIDTH - (isaac_size + 1)) {
    isaac_x += 2;
    tear_dx = 1;
    tear_dy = 0;
  }

  if (arduboy.pressed(LEFT_BUTTON) && isaac_x > 1) {
    isaac_x -= 2;
    tear_dx = -1;
    tear_dy = 0;
  }

  if (arduboy.pressed(DOWN_BUTTON) && isaac_y < HEIGHT - (isaac_size + 1)) {
    isaac_y += 2;
    tear_dx = 0;
    tear_dy = 1;
  }

  if (arduboy.pressed(UP_BUTTON) && isaac_y > 1) {
    isaac_y -= 2;
    tear_dx = 0;
    tear_dy = -1;
  }
    // draw isaac
  arduboy.drawSlowXYBitmap(isaac_x, isaac_y, ISAAC_ART, isaac_size, isaac_size, WHITE);
}

void draw_tears() {
  // for now, only allowing 1 tear on screen at a time
  if (arduboy.pressed(B_BUTTON) && tear_x == -1) {
    tear_x = isaac_x + 8 + tear_dx;
    tear_y = isaac_y + 8 + tear_dy;
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
