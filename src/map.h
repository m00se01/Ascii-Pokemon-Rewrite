#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <ncurses.h>

#include "main.h"
#include "perlin.h"

# define MAP_X 80
# define MAP_Y 21

typedef enum terrain_type {
  ter_boulder,
  ter_tree,
  ter_path,
  ter_mart,
  ter_center,
  ter_grass,
  ter_clearing,
  ter_mountain,
  ter_forest,
  ter_exit,
  num_terrain_types
} terrain_type_t;

typedef struct map {
    terrain_type_t map[MAP_Y][MAP_X];  
} map_t;

terrain_type_t get_terrain(double noiseValue);


void generate_terrain();


#endif