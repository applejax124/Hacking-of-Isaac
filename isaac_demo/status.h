#include <Arduboy2.h>

#include "isaac.h"

#ifndef STATUS_H
#define STATUS_H

#define STATUS_BAR_HEIGHT 10
#define LIFE_TOKEN_SPACING 1

void draw_status(Arduboy2 * arduboy, Isaac * r, int height);

#endif
