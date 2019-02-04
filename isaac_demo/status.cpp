#include "status.h"

#include "Arduboy2.h"

void draw_status(Arduboy2 * arduboy, Isaac * i, int height) {
  int life_token_radius = height / 2 - LIFE_TOKEN_SPACING;
  int life_token_y = LIFE_TOKEN_SPACING + life_token_radius / 2;
  int life_token_x = LIFE_TOKEN_SPACING + life_token_radius / 2;
  for (int a = i->life; a > 0; a--) {
    // TODO: include a projectile header and use actual tear size.
    arduboy->fillCircle(life_token_x, life_token_y, 1, WHITE);
    life_token_x += LIFE_TOKEN_SPACING + life_token_radius / 2;
  }
}
