#include <random>
#include <vector>
#include <iostream>
#include <cmath>
#include <iostream>

class Perlin{

private:
    int permutation_table[512];
    
    // Linear Interpolation Formula
    double lerp(double t, double a, double b){
        return a + t * (b-a);
    }
    
public:
    Perlin(){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(0,256);
    
        // Shuffle
        for (int i = 0; i < 256; ++i) {
            permutation_table[i] = i;
        }
        for (int i = 0; i < 256; ++i) {
            int j = dist(gen);
            std::swap(permutation_table[i], permutation_table[j]);
            permutation_table[i + 256] = permutation_table[i];
        }
    }

    // Fade Function
    double fade(double t){
        return t * t * t * (t * (t * 6 - 15) + 10);
    }

    // Compute gradient dot product
    double grad(int hash, double x, double y, double z) {
        int h = hash & 15;                      // Convert low 4 bits of hash code into 12 gradient directions
        double u = h < 8 ? x : y,
               v = h < 4 ? y : h == 12 || h == 14 ? x : z;
        return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
    }

    double noise(double x, double y, double z){
        // Unit cube points
        int X = (int)std::floor(x) & 255;
        int Y = (int)std::floor(y) & 255;
        int Z = (int)std::floor(z) & 255;

        // Relative positions of points in the cube
        x -= std::floor(x); 
        y -= std::floor(y);
        z -= std::floor(z);

        double u = fade(x), v = fade(y), w = fade(z);  //Fade function for x,y,z

        // Hash Coordinates of the 8 cube corners
        int A = permutation_table[X] + Y,
            AA = permutation_table[A] + Z,
            AB = permutation_table[A + 1] + Z;
        
        int  B = permutation_table[X + 1],
             BA = permutation_table[B + Z],
             BB = permutation_table[B +1] + Z;

         return lerp(w, lerp(v, lerp(u, grad(permutation_table[AA], x, y, z),  // Interpolate along x-axis
                                        grad(permutation_table[BA], x - 1, y, z)),
                                lerp(u, grad(permutation_table[AB], x, y - 1, z),
                                        grad(permutation_table[BB], x - 1, y - 1, z))),

                        lerp(v, lerp(u, grad(permutation_table[AA + 1], x, y, z - 1),  // Interpolate along x-axis
                                        grad(permutation_table[BA + 1], x - 1, y, z - 1)),
                                lerp(u, grad(permutation_table[AB + 1], x, y - 1, z - 1),
                                        grad(permutation_table[BB + 1], x - 1, y - 1, z - 1))));
    }


    void print_values(int width, int height, double scale){
        
        double max_noise_value = std::numeric_limits<double>::max();
        double min_noise_value = std::numeric_limits<double>::min();

        int i,j;
        for(i=0; i<height; i++){
            for(j=0; j<width; j++){
                double nx = i * scale;
                double ny = j * scale;
                double noiseValue = noise(nx,ny,0.0);  //2D noise

                // Normalize
                max_noise_value = std::max(max_noise_value,noiseValue);
                min_noise_value = std::min(min_noise_value,noiseValue);

                double normalize_noise_value = (noiseValue - min_noise_value) / (max_noise_value - min_noise_value);
                std::cout << normalize_noise_value;
            }
            std::cout << std::endl;
        }
    }


};
