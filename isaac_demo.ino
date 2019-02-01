#include <Arduboy2.h>

Arduboy2 arduboy;

const uint8_t PROGMEM isaac[] = {
  0x07, 0xE0, 0x0D, 0xB0, 0x1B, 0xD8, 0x39, 0x9C, 
  0x79, 0x9E, 0x7F, 0xFE, 0x7E, 0x7E, 0x3C, 0x3C, 
  0x1C, 0x38, 0x0F, 0xF0, 0x03, 0xC0, 0x1F, 0xF8, 
  0x1F, 0xF8, 0x07, 0xE0, 0x07, 0xE0, 0x06, 0x60};

int isaac_x = 64;
int isaac_y = 31;
int isaac_size = 16;

int tear_range = 0;
int tear_max_range = 12;
int tear_x = -1;
int tear_y = -1;
int tear_dx = 1;
int tear_dy = 0;

typedef struct Isaac {
  int x = 64;
  int y = 31;
  int size = 16;
} Isaac;

void setup() {
  arduboy.begin();
  arduboy.setFrameRate(30);
}

void loop() {
  if (!(arduboy.nextFrame())) {
    return;
  }
  arduboy.clear();
  
  draw_isaac();
  draw_tears();

  // this is a great way to debug lmao
  arduboy.setCursor(10, 10);
  arduboy.print(tear_x);
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
  arduboy.drawSlowXYBitmap(isaac_x, isaac_y, isaac, isaac_size, isaac_size, WHITE);
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

