#ifndef PERLIN_H
#define PERLIN_H

#include <random>
#include <vector>
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <fstream>


class Perlin {
    private:
         int permutation_table[512];

         double lerp(double t, double a, double b);

    public:
        Perlin();
        
        double fade(double t);

        double grad(int hash, double x, double y, double z);

        double noise(double x, double y, double z);

        // void print_values(int width, int height, double scale);
};


#endif