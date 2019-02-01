#include <enemy.h>
#include <isaac.h>
#include <Arduboy2.h>

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

void setup() {
  arduboy.begin();
  arduboy.setFrameRate(30);
  
}

void loop() {
  if (!(arduboy.nextFrame())) {
    return;
  }
  arduboy.clear();

  draw_enemy(f1);
  draw_enemy(p1);
  draw_isaac();
  draw_tears();

  // this is a great way to debug lmao
  //arduboy.setCursor(40, 40);
  //arduboy.print(tear_x);
  arduboy.display();
}

void draw_enemy(Enemy enemy){
  arduboy.drawSlowXYBitmap(enemy.xpos, enemy.ypos, enemy.bmp, enemy.width, enemy.height, WHITE);
}

void draw_isaac() {
  
  // move isaac according to d-pad input
  if (arduboy.pressed(RIGHT_BUTTON) && isaac.xpos < WIDTH - (isaac.width + 1)) {
    isaac.xpos += 2;
    tear_dx = 1;
    tear_dy = 0;
  }

  if (arduboy.pressed(LEFT_BUTTON) && isaac.xpos > 1) {
    isaac.xpos -= 2;
    tear_dx = -1;
    tear_dy = 0;
  }

  if (arduboy.pressed(DOWN_BUTTON) && isaac.ypos < HEIGHT - (isaac.height + 1)) {
    isaac.ypos += 2;
    tear_dx = 0;
    tear_dy = 1;
  }

  if (arduboy.pressed(UP_BUTTON) && isaac.ypos > 1) {
    isaac.ypos -= 2;
    tear_dx = 0;
    tear_dy = -1;
  }

  // draw isaac
  arduboy.drawSlowXYBitmap(isaac.xpos, isaac.ypos, isaac.bmp, isaac.width, isaac.height, WHITE);
}




void draw_tears() {
  
  // for now, only allowing 1 tear on screen at a time
  if (arduboy.pressed(B_BUTTON) && tear_x == -1) {
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
