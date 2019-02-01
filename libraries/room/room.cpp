#include "room.h"

#include "Arduboy2.h"

// Draws all features of the room within the space specified.
void draw_room(Arduboy2 * a, Room * r, int top_margin) {
  // Draw doors.
  // For each possible door, check if it should be drawn.
  if (r->doors[0]) {
    a->fillRect((WIDTH/2-ROOM_DOOR_WIDTH/2),
                top_margin+ROOM_DOOR_THICKNESS, ROOM_DOOR_WIDTH,
                ROOM_DOOR_THICKNESS, WHITE);
  }
  if (r->doors[1]) {
    a->fillRect(WIDTH-ROOM_DOOR_THICKNESS,
                (HEIGHT-top_margin)/2 - ROOM_DOOR_WIDTH/2 + top_margin,
                ROOM_DOOR_THICKNESS, ROOM_DOOR_WIDTH, WHITE);
  }
  if (r->doors[2]) {
    a->fillRect((WIDTH/2-ROOM_DOOR_WIDTH/2),
                HEIGHT-ROOM_DOOR_THICKNESS, ROOM_DOOR_WIDTH,
                ROOM_DOOR_THICKNESS, WHITE);
  }
  if (r->doors[3]) {
    a->fillRect(0,
                (HEIGHT-top_margin)/2 - ROOM_DOOR_WIDTH/2 + top_margin,
                ROOM_DOOR_THICKNESS, ROOM_DOOR_WIDTH, WHITE);
  }
}
