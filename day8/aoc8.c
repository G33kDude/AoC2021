
#define UNICODE

#include <mcl.h>
#include "ahk.h"

MCL_EXPORT(part1);
int part1(Object* input) {

    int sum = 0;
    for (int i = 0; i < input->cFields; i++) {
        Object* output_displays = input->pFields[i].pobjValue->pFields[1].pobjValue;

        for (int j = 0; j < output_displays->cFields; j++) {
            int segments = output_displays->pFields[j].ccValue - 1;

            switch(segments)
            {
                case 2: sum++; break; // 1
                case 4: sum++; break; // 4
                case 3: sum++; break; // 7
                case 7: sum++; break; // 8
            }
        }
    }

    return sum;
}