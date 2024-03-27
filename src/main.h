
#ifndef MAIN_H
#define MAIN_H

# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>

# include "utils.h"


# define MAP_X 80
# define MAP_Y 21
# define WORLD_SIZE 401



typedef enum __attribute__ ((__packed__)) terrain_type {
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

typedef struct world{
    // Array of map_t pointers
    map_t * world_array[WORLD_SIZE][WORLD_SIZE];
    // Pointer to the current map being displayed
    map_t * curr_map;

    pair_t curr_index;

    bool quit;
} world_t;

extern world_t world; 

extern pair_t all_dirs[8];

int generate_new_map();

#endif