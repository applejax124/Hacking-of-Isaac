#include <Arduboy2.h>
#include "isaac.h"

#ifndef ENEMY_H
#define ENEMY_H

const uint8_t PROGMEM fly_bmp[] = {
  0xE1, 0xC0, 0x92, 0x40, 0x9E, 0x40, 0x7F, 0x80,
  0x1E, 0x00, 0x1E, 0x00};

const uint8_t PROGMEM pooter_bmp[] = {
  0x0E, 0x00, 0xF2, 0x00, 0x92, 0x00, 0x9F, 0x00, 
  0x75, 0x00, 0x15, 0x00, 0x3F, 0x80, 0x3F, 0x80, 
  0x3F, 0x80, 0x1F, 0x00, 0x0E, 0x00, 0x00, 0x00};

typedef enum enemy_type {F, P} enemy_type;

#define POOTER_SPEEDX   0   //pooters don't move
#define POOTER_SPEEDY   0
#define POOTER_LIVES    1   //pooters only have 1 life

#define FLY_SPEEDX  1   //flies move at 1/2 the speed of isaac
#define FLY_SPEEDY  1
#define FLY_LIVES   1   //flies only have 1 life

typedef struct Enemy {
  uint8_t xpos;
  uint8_t ypos;
  uint8_t height;
  uint8_t width;
  uint8_t speedx;
  uint8_t speedy;
  enemy_type type; 
  const uint8_t * bmp;
  uint8_t life;
  bool exists;
} Enemy;

void draw_enemy(Arduboy2 * arduboy, Enemy * e);
void move_enemy(Enemy*, Isaac*);
void delete_enemy(Enemy * e, int * num_enemies,
                  const int enemy_index);
#endif
