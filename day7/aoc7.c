
#define UNICODE

#include <mcl.h>
#include "ahk.h"

MCL_EXPORT(part1);
int part1(Object* input) {

    // Compute bounds, optimal midpoint will not be outside crab cluster
    int min = input->pFields[0].iValue, max = min;
    for (int i = 0; i < input->cFields; i++) {
        int val = input->pFields[i].iValue;
        if (val < min) { min = val; }
        if (val > max) { max = val; }
    }

    // Find the smallest sum of deltas
    int minsum = 0x7FFFFFFF;
    for (int j = min; j <= max; j++) {
        int sum = 0;
        for (int i = 0; i < input->cFields; i++) {
            int delta = input->pFields[i].iValue - j;
            if (delta < 0) { delta = -delta; }
            sum += delta;
        }
        if (sum < minsum) { minsum = sum; }
    }

    return minsum;
}

MCL_EXPORT(part2);
uint64_t part2(Object* input) {

    // Compute bounds, optimal midpoint will not be outside crab cluster
    int min = input->pFields[0].iValue, max = min;
    for (int i = 0; i < input->cFields; i++) {
        int val = input->pFields[i].iValue;
        if (val < min) { min = val; }
        if (val > max) { max = val; }
    }

    // Find the smallest sum of deltas using addition series sum algorithm
    uint64_t minsum = ~0;
    for (int j = min; j <= max; j++) {
        uint64_t sum = 0;
        for (int i = 0; i < input->cFields; i++) {
            int delta = input->pFields[i].iValue - j;
            if (delta < 0) { delta = -delta; }
            sum += (delta+1)*delta/2;
        }
        if (sum < minsum) { minsum = sum; }
    }

    return minsum;
}
