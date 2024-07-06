#include <vector>
#include <cmath>
#include <random>
#include <algorithm>

// Function prototypes
float fade(float t);
float lerp(float t, float a, float b);
float grad(int hash, float x, float y);
float noise(float x, float y);

// Permutation table
std::vector<int> p(256);

// Initialize the permutation table
void initPermutationTable() {
    for (int i = 0; i < 256; i++) {
        p[i] = i;
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(p.begin(), p.end(), g);
    p.insert(p.end(), p.begin(), p.end()); // Duplicate the array
}

// Helper functions for Perlin noise
float fade(float t) {
    return t * t * t * (t * (t * 6 - 15) + 10);
}

float lerp(float t, float a, float b) { 
    return a + t * (b - a); 
}

float grad(int hash, float x, float y) {
    int h = hash & 15;
    float u = h < 8 ? x : y;
    float v = h < 4 ? y : (h == 12 || h == 14 ? x : 0);
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

// Perlin noise function
float noise(float x, float y) {
    const float SEED = 1337.0f;
    x += SEED;
    y += SEED;
    int X = (int)floor(x) & 255;
    int Y = (int)floor(y) & 255;
    x -= floor(x);
    y -= floor(y);
    float u = fade(x);
    float v = fade(y);
    int A = p[X] + Y, B = p[X + 1] + Y;
    return lerp(v, lerp(u, grad(p[A], x, y), grad(p[B], x - 1, y)),
                lerp(u, grad(p[A + 1], x, y - 1), grad(p[B + 1], x - 1, y - 1)));
}