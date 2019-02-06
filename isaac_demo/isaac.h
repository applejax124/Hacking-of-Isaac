#include <Arduboy2.h>
#include "status.h"

#ifndef ISAAC_H
#define ISAAC_H

#define ISAAC_HEIGHT 16
#define ISAAC_WIDTH 16

#define ISAAC_SPEEDX 2
#define ISAAC_SPEEDY 2

#define ISAAC_LIVES 3

const uint8_t PROGMEM isaac_bmp[] = {
  0x07, 0xE0, 0x0D, 0xB0, 0x1B, 0xD8, 0x39, 0x9C, 
  0x79, 0x9E, 0x7F, 0xFE, 0x7E, 0x7E, 0x3C, 0x3C, 
  0x1C, 0x38, 0x0F, 0xF0, 0x03, 0xC0, 0x1F, 0xF8, 
  0x1F, 0xF8, 0x07, 0xE0, 0x07, 0xE0, 0x06, 0x60};

typedef struct Isaac {
  int xpos;
  int ypos;
  const uint8_t height;
  const uint8_t width;
  int speedx;
  int speedy;
  const uint8_t * bmp;
  const uint8_t life;
} Isaac;

void draw_isaac(Arduboy2 * arduboy, Isaac * isaac);
void move_isaac(Arduboy2 * arduboy, Isaac * isaac);
void update_isaac_position(Isaac * i, int x_pos, int y_pos);

#endif
