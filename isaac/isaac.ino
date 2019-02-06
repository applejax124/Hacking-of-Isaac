#include <Arduboy2.h>

const uint8_t PROGMEM fly_bmp[] = {
  0xE1, 0xC0, 0x92, 0x40, 0x9E, 0x40, 0x7F, 0x80,
  0x1E, 0x00, 0x1E, 0x00};

const uint8_t PROGMEM pooter_bmp[] = {
  0x0E, 0x00, 0xF2, 0x00, 0x92, 0x00, 0x9F, 0x00, 
  0x75, 0x00, 0x15, 0x00, 0x3F, 0x80, 0x3F, 0x80, 
  0x3F, 0x80, 0x1F, 0x00, 0x0E, 0x00, 0x00, 0x00};

typedef enum enemy_type {F, P} enemy_type;

typedef struct Enemy {
  int xpos;
  int ypos;
  int height;
  int width;
  int speedx;
  int speedy;
  enemy_type type; 
  const uint8_t * bmp;
  int life;
} Enemy;

void draw_enemy(Arduboy2 * arduboy, Enemy * e);

#define ISAAC_HEIGHT 16
#define ISAAC_WIDTH 16

const uint8_t PROGMEM isaac_bmp[] = {
  0x07, 0xE0, 0x0D, 0xB0, 0x1B, 0xD8, 0x39, 0x9C, 
  0x79, 0x9E, 0x7F, 0xFE, 0x7E, 0x7E, 0x3C, 0x3C, 
  0x1C, 0x38, 0x0F, 0xF0, 0x03, 0xC0, 0x1F, 0xF8, 
  0x1F, 0xF8, 0x07, 0xE0, 0x07, 0xE0, 0x06, 0x60};

typedef struct Isaac {
  int xpos;
  int ypos;
  int height; 
  int width;
  int speedx;
  int speedy;
  const uint8_t * bmp;
  int life;
} Isaac;

void draw_isaac(Arduboy2 * arduboy, Isaac * isaac);
void move_isaac(Arduboy2 * arduboy, Isaac * isaac);
void update_isaac_position(Isaac * i, int x_pos, int y_pos);

typedef enum projectile_type {I, H} projectile_type;

typedef struct Projectile {
  int xpos;
  int ypos;
  int range;
  int speedx;
  int speedy;
  projectile_type type;
} Projectile;

#define DOOR_WIDTH 16
#define DOOR_THICKNESS 4

typedef struct Room {
  //Enemy enemies[];
  //Obstacle obstacles[];
  int doors[4];
  bool cleared;
  bool is_in_map;
} Room;

typedef struct Map {
  bool cleared;
  Room rooms[9];
  int active_room;
} Map;

void create_rooms(Map *m, int level[]);
void draw_room(Arduboy2 * arduboy, Room * r, int top_margin);
void check_use_door(Map * m, Isaac * i, int top_margin, int num_enemies);

#define STATUS_BAR_HEIGHT 10
#define LIFE_TOKEN_SPACING 1

void draw_status(Arduboy2 * arduboy, Isaac * r, int height);


Arduboy2 arduboy;

int tear_range = 0;
int tear_max_range = 12;
int tear_x = -1;
int tear_y = -1;
int tear_dx = 1;
int tear_dy = 0;


Enemy f1 = {20, 20, 6, 10, 1, 1, F, fly_bmp, 2};
Enemy p1 = {30, 30, 11, 9, 1, 1, P, pooter_bmp, 3};
// TODO: the code currently assumes enemey lists will follow a pattern
//        of tracking size with a seperate integer.
int enemy_count = 0;
Isaac isaac = {40, 40, ISAAC_HEIGHT, ISAAC_WIDTH, 2, 2, isaac_bmp, 3};
Room r = {.doors = {0,1,1,0}, .cleared = 0 };
Room r1 = {.doors = {0,1,1,1}, .cleared = 0 };
Room r2 = {.doors = {0,0,1,1}, .cleared = 0 };
Room r3 = {.doors = {1,1,1,0}, .cleared = 0 };
Room r4 = {.doors = {1,1,1,1}, .cleared = 0 };
Room r5 = {.doors = {1,0,1,1}, .cleared = 0 };
Room r6 = {.doors = {1,1,0,0}, .cleared = 0 };
Room r7 = {.doors = {1,1,0,1}, .cleared = 0 };
Room r8 = {.doors = {1,0,0,1}, .cleared = 0 };
//Map m = create_map();
Map m;

/*
 * 
 * SETUP FUNCTION
 * 
 */
void setup() {
  arduboy.begin();
  arduboy.setFrameRate(30);
  m.active_room = 0;
  m.rooms[0] = r;
  m.rooms[1] = r1;
  m.rooms[2] = r2;
  m.rooms[3] = r3;
  m.rooms[4] = r4;
  m.rooms[5] = r5;
  m.rooms[6] = r6;
  m.rooms[7] = r7;
  m.rooms[8] = r8;
}

/*
 * 
 * LOOP FUNCTION
 * 
 */
void loop() {
  if (!(arduboy.nextFrame())) {
    return;
  }
  arduboy.clear();

  draw_enemy(&arduboy, &f1);
  draw_enemy(&arduboy, &p1);
  draw_room(&arduboy, &m.rooms[m.active_room], STATUS_BAR_HEIGHT);
  draw_status(&arduboy, &isaac, STATUS_BAR_HEIGHT);
  draw_isaac(&arduboy, &isaac);
  
  move_isaac(&arduboy, &isaac);
  check_use_door(&m, &isaac, STATUS_BAR_HEIGHT, enemy_count);

  arduboy.setCursor(50, 20);
  arduboy.print(m.active_room);

  arduboy.display();
}


/*
 * Draw Projectiles
 */

void draw_projectiles() {

  // 
  
  // for now, only allowing 1 tear on screen at a time
  if (arduboy.pressed(B_BUTTON)) {
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

void draw_enemy(Arduboy2 * arduboy, Enemy * e){

  arduboy->drawSlowXYBitmap(e->xpos, e->ypos, e->bmp, e->width, e->height, WHITE);

};

void move_isaac(Arduboy2 * arduboy, Isaac * isaac){

  if (arduboy->pressed(RIGHT_BUTTON) && isaac->xpos < WIDTH - (isaac->width + 1)) {
    isaac->xpos += isaac->speedx;
  }else if (arduboy->pressed(LEFT_BUTTON) && isaac->xpos > 1) {
    isaac->xpos -= isaac->speedx;
  }else if (arduboy->pressed(DOWN_BUTTON) && isaac->ypos < HEIGHT - (isaac->height + 1)) {
    isaac->ypos += isaac->speedy;
  }else if (arduboy->pressed(UP_BUTTON) && isaac->ypos > STATUS_BAR_HEIGHT) {
    isaac->ypos -= isaac->speedy;
  }

}

void draw_isaac(Arduboy2 * arduboy, Isaac * isaac){

  arduboy->drawSlowXYBitmap(isaac->xpos, isaac->ypos, isaac->bmp, isaac->width, isaac->height, WHITE);

}

// Changes the coordinates of Isaac.
void update_isaac_position(Isaac * i, int x_pos, int y_pos) {
  i->xpos = x_pos;
  i->ypos = y_pos;
}

void add_friendlies();

void add_enemies();

void move_projectiles();

void draw_projectiles();

int LEVEL = 1;

int level1[] = {0, 1, 0, 1, 1, 1, 0, 1, 0};
int level2[] = {1, 1, 1, 1, 0, 1, 1, 0, 1};
int level3[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};

// Draws all features of the room within the space specified.
void draw_room(Arduboy2 * arduboy, Room * r, int top_margin) {
  if (r->doors[0]) {
    arduboy->fillRect(WIDTH/2 - DOOR_WIDTH/2,
                      top_margin + DOOR_THICKNESS,
                      DOOR_WIDTH, DOOR_THICKNESS, WHITE);
  }
  if (r->doors[1]) {
    arduboy->fillRect(WIDTH - DOOR_THICKNESS,
                      (HEIGHT - top_margin)/2 - DOOR_WIDTH/2 + top_margin,
                      DOOR_THICKNESS, DOOR_WIDTH, WHITE);
  }
  if (r->doors[2]) {
    arduboy->fillRect(WIDTH/2 - DOOR_WIDTH/2,
                      HEIGHT - DOOR_THICKNESS,
                      DOOR_WIDTH, DOOR_THICKNESS, WHITE);
  }
  if (r->doors[3]) {
    arduboy->fillRect(0, (HEIGHT - top_margin)/2 - DOOR_WIDTH/2 + top_margin,
                      DOOR_THICKNESS, DOOR_WIDTH, WHITE);
  }
}


Map create_map() {
  Map *m;
  if (LEVEL == 1) {
    create_rooms(m, level1);
  } else if (LEVEL == 2) {
    create_rooms(m, level2);
  } else if (LEVEL == 3) {
    create_rooms(m, level3);
  }
}

void create_rooms(Map *m, int level[]) {
  for (int i = 0; i < 9; i++) {
    if (!level[i]) {
      //Room r = {.is_in_map = false};
      Room r;
      r.is_in_map = false;
      m->rooms[i] = r;
      continue;
    }

    //Room r = {.cleared = 0, .is_in_map = 0};
    Room r;
    r.cleared = 0;
    r.is_in_map = false;
    m->rooms[i] = r;
  }

  for (int i = 0; i < 9; i++) {
    m->rooms[i].doors[0] =  i > 2       && m->rooms[i-3].is_in_map ? 1 : 0; // up
    m->rooms[i].doors[1] = (i % 3) - 2  && m->rooms[i+1].is_in_map ? 1 : 0; // right
    m->rooms[i].doors[2] = i < 6        && m->rooms[i+3].is_in_map ? 1 : 0; // down
    m->rooms[i].doors[3] == i % 3       && m->rooms[i-1].is_in_map ? 1 : 0; // left
  }
}


// TODO: The constatnts used mary the system to a 3x3 grid, should abstract.
// TODO: Isaac should have a built-in reset method.
void check_use_door(Map * m, Isaac * i, int top_margin, int num_enemies) {
  if ((m->rooms[m->active_room].doors[0]) &&
      (i->xpos + ISAAC_WIDTH > WIDTH/2 - DOOR_WIDTH/2) && 
      (i->xpos < WIDTH/2 + DOOR_WIDTH/2) &&
      (i->ypos < top_margin + DOOR_THICKNESS) &&
      (num_enemies < 1) &&
      (m->active_room > 2)) {
    m->active_room -= 3;
    update_isaac_position(i, i->xpos, HEIGHT-i->ypos - 2*DOOR_THICKNESS);
  }
  if ((m->rooms[m->active_room].doors[1]) &&
      (i->ypos + ISAAC_HEIGHT > HEIGHT/2 - DOOR_WIDTH/2 + top_margin/2) && 
      (i->ypos < HEIGHT/2 + DOOR_WIDTH/2 + top_margin/2) &&
      (i->xpos + ISAAC_WIDTH > WIDTH - DOOR_THICKNESS) &&
      (num_enemies < 1) &&
      (m->active_room < 8)) {
    m->active_room += 1;
    update_isaac_position(i, WIDTH-i->xpos + DOOR_THICKNESS, i->ypos);
  }
  if ((m->rooms[m->active_room].doors[2]) &&
      (i->xpos + ISAAC_WIDTH > WIDTH/2 - DOOR_WIDTH/2) && 
      (i->xpos < WIDTH/2 + DOOR_WIDTH/2) &&
      (i->ypos + ISAAC_HEIGHT > HEIGHT - DOOR_THICKNESS) &&
      (num_enemies < 1) &&
      (m->active_room < 6)) {
    m->active_room += 3;
    update_isaac_position(i, i->xpos, HEIGHT-i->ypos + DOOR_THICKNESS);
  }
  if ((m->rooms[m->active_room].doors[3]) &&
      (i->ypos + ISAAC_HEIGHT > HEIGHT/2 - DOOR_WIDTH/2 + top_margin/2) && 
      (i->ypos < HEIGHT/2 + DOOR_WIDTH/2 + top_margin/2) &&
      (i->xpos < DOOR_THICKNESS) &&
      (num_enemies < 1) && 
      (m->active_room > 0)) {
    m->active_room -= 1;
    update_isaac_position(i, WIDTH-i->xpos - 4*DOOR_THICKNESS, i->ypos);
  }
}

void draw_status(Arduboy2 * arduboy, Isaac * i, int height) {
  int life_token_radius = height / 2 - LIFE_TOKEN_SPACING;
  int life_token_y = LIFE_TOKEN_SPACING + life_token_radius;
  int life_token_x = LIFE_TOKEN_SPACING + life_token_radius;
  for (int a = i->life; a > 0; a--) {
    // TODO: include a projectile header and use actual tear size.
    arduboy->fillCircle(life_token_x, life_token_y, life_token_radius, WHITE);
    life_token_x += LIFE_TOKEN_SPACING + life_token_radius * 2;
  }
}
