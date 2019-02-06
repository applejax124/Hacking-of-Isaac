#include <Arduboy2.h>

#include "enemy.h"
#include "isaac.h"
#include "projectile.h"
#include "room.h"
#include "status.h"

//TODO: instantiations -- (arduboy, isaac, map, ??)
Arduboy2 arduboy;
Isaac isaac = {40, 40, ISAAC_HEIGHT, ISAAC_WIDTH, 0, 0, isaac_bmp, ISAAC_LIVES};
Map m = create_map();

//TODO: setup function
void setup() {
  arduboy.begin();
  arduboy.setFrameRate(30);
}


//TODO: loop function
void loop() {

  //clear the current screen
  if (!(arduboy.nextFrame())) {
    return;
  }
  arduboy.clear();

  //TODO: draw room
  draw_room(&arduboy, &m.rooms[m.active_room], &isaac, STATUS_BAR_HEIGHT);

  //TODO: draw status bar
  draw_status(&arduboy, &isaac, STATUS_BAR_HEIGHT);

  //TODO: update room --> updates the location of each of the elements in the room
  update_room(&arduboy, &isaac, &m.rooms[m.active_room]);
  check_use_door(&m, &isaac, STATUS_BAR_HEIGHT,  m.rooms[m.active_room].n_enemies);

  arduboy.setCursor(50, 20);
  arduboy.print(m.active_room);


  //needed to display everything associated with arduboy object
  arduboy.display();
}
