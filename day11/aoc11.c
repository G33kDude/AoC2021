
#define UNICODE

#include <mcl.h>
#include "ahk.h"
#include <stdlib.h>

int step(UCHAR* input) {
    int flashes = 0;

    // First, the energy level of each octopus increases by 1
    for (int i = 0; i < 100; i++) {
        input[i]++;
    }

    // Then, any octopus with an energy level greater than 9 flashes. This
    // increases the energy level of all adjacent octopuses by 1, including
    // octopuses that are diagonally adjacent. If this causes an octopus to have
    // an energy level greater than 9, it also flashes. This process continues
    // as long as new octopuses keep having their energy level increased beyond
    // 9. (An octopus can only flash at most once per step.)
    bool flashed = true;
    while (flashed) {
        flashed = false;

        for (int y = 0; y < 10; y++) {
            for (int x = 0; x < 10; x++) {

                if (input[10*y+x] > 9){
                    flashed = true;

                    input[10*y+x] = 0;
                    flashes++;

                    if (x >  0 && y >  0 && input[10*(y-1)+(x-1)] > 0) { input[10*(y-1)+(x-1)]++; }
                    if (x >  0           && input[10*(y  )+(x-1)] > 0) { input[10*(y  )+(x-1)]++; }
                    if (x >  0 && y <  9 && input[10*(y+1)+(x-1)] > 0) { input[10*(y+1)+(x-1)]++; }
                    if (          y >  0 && input[10*(y-1)+(x  )] > 0) { input[10*(y-1)+(x  )]++; }
                    if (          y <  9 && input[10*(y+1)+(x  )] > 0) { input[10*(y+1)+(x  )]++; }
                    if (x <  9 && y >  0 && input[10*(y-1)+(x+1)] > 0) { input[10*(y-1)+(x+1)]++; }
                    if (x <  9           && input[10*(y  )+(x+1)] > 0) { input[10*(y  )+(x+1)]++; }
                    if (x <  9 && y <  9 && input[10*(y+1)+(x+1)] > 0) { input[10*(y+1)+(x+1)]++; }
                }

            }
        }
    }

    return flashes;
}


MCL_EXPORT(part1);
int part1(UCHAR* input) {
    int sum = 0;

    for (int i = 0; i < 100; i++) {
        sum += step(input);
    }

    return sum;
}

MCL_EXPORT(part2);
int part2(UCHAR* input) {
    int i = 0;
    bool allzed = false;

    while (!allzed) {
        step(input);
        i++;

        allzed = true;
        for (int j = 0; j < 100; j++) {
            if (input[j] == 0) continue;
            allzed = false;
            break;
        }
    }

    return i;
}