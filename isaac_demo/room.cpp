#include "room.h"

// Draws all features of the room within the space specified.
void draw_room(Arduboy2 arduboy, Room r) {

  int door_width = 16;
  int door_thickness = 4;
  int top_margin = 10;

  if (r.doors[0]) {
    arduboy.fillRect(WIDTH/2 - door_width/2,
               top_margin + door_thickness, door_width, door_thickness, WHITE);
  }
  if (r.doors[1]) {
    arduboy.fillRect(WIDTH - door_thickness,
               (HEIGHT - top_margin)/2 - door_width/2 + top_margin, door_thickness, door_width, WHITE);
  }
  if (r.doors[2]) {
    arduboy.fillRect(WIDTH/2 - door_width/2,
               HEIGHT - door_thickness, door_width, door_thickness, WHITE);
  }
  if (r.doors[3]) {
    arduboy.fillRect(0,
               (HEIGHT - top_margin)/2 - door_width/2 + top_margin, door_thickness, door_width, WHITE);
  }
}
