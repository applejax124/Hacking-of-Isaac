#include <Arduboy2.h>
#include <isaac.h>
#include <projectile.h>
#include <enemy.h>
#include <status.h>

// Use xpos and ypos to frame each object

// Put this in a loop where i < the number of obstacles in the room
// Put this in a while loopfor while obstacles are enabled
Rect isaacRect = Rect{isaac.xpos, isaac.ypos, isaac.xpos+isaac.width, isaac.ypos-isaac.height};

if (enemy.type[0] == F) {
    Rect flyRect = Rect{enemy.xpos, enemy.ypos, enemy.xpos+enemy.width, enemy.ypos-enemy.height};
}
else if (enemy.type[0] == P) {
    Rect.pooterRect = Rect{enemy.xpos, enemy.ypos, enemy.xpos+enemy.width, enemy.ypos-enemy.height};
}

// Put in while loop the checks life count
if (arduboy.collide((isaacRect, flyRect) || (isaacRect, pooterRect) {
 // Remove a life 
 
}

    
