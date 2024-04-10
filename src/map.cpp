#include <iostream>
#include <ncurses.h>
#include <fstream>

#include "main.h"
#include "perlin.h"
#include "map.h"


// TODO: Adjust Values for terrain generation based on the noise map
 terrain_type get_terrain(double noiseValue){
        if(noiseValue > 0.7 && noiseValue < .9){
            return ter_boulder;
        }
        else if (noiseValue > 0.5 && noiseValue < 0.7)
        {
            return ter_clearing;
        }
        else if (noiseValue > 0.4 && noiseValue < .5)
        {
            return ter_clearing;
        }
          else if (noiseValue > .1 && noiseValue < .3)
        {
            return ter_grass;
        }else{
            return ter_grass;
        }
}

void generate_terrain(){

    Perlin perlin;

    double min_noise_value = std::numeric_limits<double>::min();
    double max_noise_value = std::numeric_limits<double>::max();

    double scale = 0.1;

    int x,y;
    for(y= 0; y<MAP_Y; y++){
        for(x= 0; x<MAP_X; x++){
            double nx = x * scale;
            double ny = y * scale;
            double noiseValue = perlin.noise(nx,ny,0.0);

            max_noise_value = std::min(max_noise_value, noiseValue);
            min_noise_value = std::max(min_noise_value, noiseValue);

            double normalize_noise_value = (noiseValue - max_noise_value) / (min_noise_value - max_noise_value);

            world.curr_map->map[y][x] = get_terrain(normalize_noise_value); ;
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
}


