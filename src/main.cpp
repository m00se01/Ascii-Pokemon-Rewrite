#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdint.h>
#include <string.h>
#include <ncurses.h>

#include "main.h"
#include "io.h"
#include "perlin.h"

world_t world;

// Define an array of pairs representing eight directions TL,T,TR,L,R,BL,B,BR
pair_t all_dirs[8] = {
    { -1, -1 },  // Top-left direction
    { -1,  0 },  // Top direction
    { -1,  1 },  // Top-right direction
    {  0, -1 },  // Left direction
    {  0,  1 },  // Right direction
    {  1, -1 },  // Bottom-left direction
    {  1,  0 },  // Bottom direction
    {  1,  1 }   // Bottom-right direction
};



/*  A new map should be generated if the player
    walks into an exit located on the edges of the map 
*/
int generate_new_map(){
    // Create a new map of (MAP_Y x MAP_X)
    // If map exists at the current index, don't create a new one just set curr_map to the map at current index
    if(world.world_array[world.curr_index[dim_y]][world.curr_index[dim_x]]){
        world.curr_map = world.world_array[world.curr_index[dim_y]][world.curr_index[dim_x]];
        return 0;
    }

    // Add the map to memory
    world.curr_map = world.world_array[world.curr_index[dim_y]][world.curr_index[dim_x]] = (map_t *) malloc(sizeof (*world.curr_map));


    // TODO: Generate Random Terrain
    // TODO: For now just inititalize terrain with grass and border
    
    // Perlin perlin;
    
    
    int x,y;
    for(y= 0; y<MAP_Y; y++){
        for(x= 0; x<MAP_X; x++){
            world.curr_map->map[y][x] = ter_grass ;
        }
    }
    
    // Border Outlines
    for(y= 0; y<MAP_Y; y++)
    {    
        for(x= 0; x<MAP_X; x++)
        {
            world.curr_map->map[0][x] = ter_boulder;
            world.curr_map->map[MAP_Y-1][x] = ter_boulder;
        }

        world.curr_map->map[y][0] = ter_boulder;
        world.curr_map->map[y][MAP_X-1] = ter_boulder;
    }

    return 0;
}

// Initialize world
void init_world(){
    world.quit = false;
    // First Map is generated at the center of the world
    world.curr_index[dim_x] = world.curr_index[dim_y] = WORLD_SIZE / 2;
    generate_new_map();
}

void game_loop(){
    bool on = true;

    while(on){

        io_display();
        
        char input = getch();
        if(input == 'q'){
            mvprintw(23,1,"Exiting...");
            on = false;
        }

        refresh();
    }

}


int main(){   

    io_init();
    init_world();

    game_loop();

    io_terminate();

    return 0;    
}