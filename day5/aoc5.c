
#define UNICODE

#include <mcl.h>
#include "ahk.h"

MCL_EXPORT(part1);
int part1(Object* ocean, Object* vents) {

    // For all vent lines
    for (int vent_index = 0; vent_index < vents->cFields; vent_index++) {
        Object* vent = vents->pFields[vent_index].pobjValue;

        // x1 == x2, Vertical Line
        if (vent->pFields[0].iValue == vent->pFields[2].iValue) {
            int x = vent->pFields[0].iValue;

            // y1 < y2
            if (vent->pFields[1].iValue < vent->pFields[3].iValue) {
                // y1 -> y2
                for (int y = vent->pFields[1].iValue; y <= vent->pFields[3].iValue; y++) {
                    // Increment board value
                    ocean->pFields[y].pobjValue->pFields[x].iValue++;
                }
            } else {
                // y2 -> y1
                for (int y = vent->pFields[3].iValue; y <= vent->pFields[1].iValue; y++) {
                    // Increment board value
                    ocean->pFields[y].pobjValue->pFields[x].iValue++;
                }
            }
        }

        // y1 == y2, Horizontal Line
        else if (vent->pFields[1].iValue == vent->pFields[3].iValue) {
            int y = vent->pFields[1].iValue;

            // x1 < x2
            if (vent->pFields[0].iValue < vent->pFields[2].iValue) {
                // x1 -> x2
                for (int x = vent->pFields[0].iValue; x <= vent->pFields[2].iValue; x++) {
                    ocean->pFields[y].pobjValue->pFields[x].iValue++;
                }
            } else {
                // x2 -> x1
                for (int x = vent->pFields[2].iValue; x <= vent->pFields[0].iValue; x++) {
                    ocean->pFields[y].pobjValue->pFields[x].iValue++;
                }
            }
        }

        // Diagonal Line
        else {
            bool x_increases = vent->pFields[0].iValue < vent->pFields[2].iValue;
            bool y_increases = vent->pFields[1].iValue < vent->pFields[3].iValue;

            int x = vent->pFields[0].iValue;
            for (
                int y = vent->pFields[1].iValue;
                y_increases ? (y <= vent->pFields[3].iValue) : (y >= vent->pFields[3].iValue);
                (y_increases ? y++ : y--), (x_increases ? x++ : x--)
            ) {
                ocean->pFields[y].pobjValue->pFields[x].iValue++;
            }
        }
    }

    // Undersea vent intersection sum
    int sum = 0;

    // For all rows on ocean floor
    for (int y = 0; y < ocean->cFields; y++) {
        Object* row = ocean->pFields[y].pobjValue;

        // For all columns on ocean floor
        for (int x = 0; x < row->cFields; x++) {

            // If two or more vents intersect at this point
            if (ocean->pFields[y].pobjValue->pFields[x].iValue >= 2) {
                sum++;
            }
        }
    }

    return sum;
}