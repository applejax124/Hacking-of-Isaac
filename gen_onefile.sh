#!/bin/sh
echo "#include <Arduboy2.h>" > onefile.ino
cat isaac_demo/isaac.h isaac_demo/enemy.h isaac_demo/projectile.h\
    isaac_demo/*.h isaac_demo/isaac_demo.ino isaac_demo/*.cpp | grep -v "#include" >> onefile.ino
