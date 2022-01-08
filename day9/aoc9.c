
#define UNICODE

#include <mcl.h>
#include "ahk.h"

#define GetVent(x, y) bHMap[iHMapW*(y)+(x)]

MCL_EXPORT(part1);
int part1(UCHAR* bHMap, int iHMapW, int iHMapH) {
    int sum = 0;

    // Iterate over every vent in the height map
    for (int y = 0; y < iHMapH; y++) {
        for (int x = 0; x < iHMapW; x++) {
            UCHAR vent = GetVent(x, y);

            // Assume this is the lowest point in the basin
            bool lowest = true;

            // If any adjacent vents are lower or equal, this is not the
            // lowest point in the basin.
            if (y > 0 && GetVent(x, y-1) <= vent) lowest = false;
            if (y < iHMapH-1 && GetVent(x, y+1) <= vent) lowest = false;
            if (x > 0 && GetVent(x-1, y) <= vent) lowest = false;
            if (x < iHMapW-1 && GetVent(x+1, y) <= vent) lowest = false;

            // If it was verified as the lowest point in the basin, add its risk
            if (lowest) sum += vent + 1;
        }
    }
    return sum;
}

// Recursive flood fill (heh) of basin with 9s, returning total count of 9s set.
// Subsequent calls within the basin will return 0 because it's all 9s.
int BasinSizeAtPoint(UCHAR* bHMap, int iHMapW, int iHMapH, int x, int y) {
    // 9s are excluded from the basin
    if (GetVent(x, y) >= 9) return 0;

    // Fill this cell
    bHMap[iHMapW*y+x] = 9;

    // Basin size including this cell
    int size = 1;

    // Fill adjacent points within the map boundary and accumulate their sizes
    if (y > 0) size += BasinSizeAtPoint(bHMap, iHMapW, iHMapH, x, y-1);
    if (y < iHMapH-1) size += BasinSizeAtPoint(bHMap, iHMapW, iHMapH, x, y+1);
    if (x > 0) size += BasinSizeAtPoint(bHMap, iHMapW, iHMapH, x-1, y);
    if (x < iHMapW-1) size += BasinSizeAtPoint(bHMap, iHMapW, iHMapH, x+1, y);

    // Return the calculated basin size
    return size;
}

MCL_EXPORT(part2);
int part2(UCHAR* bHMap, int iHMapW, int iHMapH) {
    int biggest[] = {0, 0, 0};

    // Iterate over every vent in the height map
    for (int y = 0; y < iHMapH; y++) {
        for (int x = 0; x < iHMapW; x++) {

            // Flood the basin and return its size
            int size = BasinSizeAtPoint(bHMap, iHMapW, iHMapH, x, y);

            // Track the top 3 biggest basins
            if (size > biggest[2]) {
                biggest[0] = biggest[1];
                biggest[1] = biggest[2];
                biggest[2] = size;
            } else if (size > biggest[1]) {
                biggest[0] = biggest[1];
                biggest[1] = size;
            } else if (size > biggest[0]) {
                biggest[0] = size;
            }

        }
    }
    return biggest[0] * biggest[1] * biggest[2];
}
