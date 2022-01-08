
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

int count_bits(UCHAR n) {
    int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

MCL_EXPORT(part2);
int part2(Object* input) {
    UCHAR unknown_bitfields[6];
    UCHAR known_bitfields[10];
    int sum = 0;

    for (int i = 0; i < input->cFields; i++) {
        Object* row = input->pFields[i].pobjValue;

        // Randomly sorted segment configurations for digits 0-9
        Object* configs = row->pFields[0].pobjValue;

        // The four segment configurations to solve
        Object* outputs = row->pFields[1].pobjValue;

        int index_unknown_bitfields = 0;

        for (int j = 0; j < configs->cFields; j++) {
            LPTSTR config = configs->pFields[j].pstrValue;

            UCHAR bitfield = 0;
            for (int k = 0; config[k] != 0; k++) {
                bitfield |= 1 << (config[k] - 'a');
            }

            // Go ahead and save configurations for digits of known segment count
            switch (configs->pFields[j].ccValue - 1) {
                case 2: known_bitfields[1] = bitfield; break;
                case 3: known_bitfields[7] = bitfield; break;
                case 4: known_bitfields[4] = bitfield; break;
                case 7: known_bitfields[8] = bitfield; break;
                default: unknown_bitfields[index_unknown_bitfields++] = bitfield; break;
            }
        }

        for (int j = 0; j < index_unknown_bitfields; j++) {
            UCHAR bitfield = unknown_bitfields[j];
            int intersection = count_bits(bitfield) * 100
                + count_bits(bitfield & known_bitfields[4]) * 10
                + count_bits(bitfield & known_bitfields[7]);

            switch (intersection) {
                case 522: known_bitfields[2] = bitfield; break;
                case 533: known_bitfields[3] = bitfield; break;
                case 532: known_bitfields[5] = bitfield; break;
                case 633: known_bitfields[0] = bitfield; break;
                case 632: known_bitfields[6] = bitfield; break;
                case 643: known_bitfields[9] = bitfield; break;
            }
        }


        int output_four_digits = 0;
        for (int j = 0; j < outputs->cFields; j++) {
            LPTSTR config = outputs->pFields[j].pstrValue;

            UCHAR bitfield = 0;
            for (int k = 0; config[k] != 0; k++) {
                bitfield |= 1 << (config[k] - 'a');
            }

            for (int k = 0; k < 10; k++) {
                if (known_bitfields[k] == bitfield) {
                    output_four_digits *= 10;
                    output_four_digits += k;
                }
            }
        }

        sum += output_four_digits;
    }

    return sum;
}
