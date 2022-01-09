
#define UNICODE

#include <mcl.h>
#include "ahk.h"
#include <stdlib.h>


// --- Part 1 ---

int score(LPTSTR* pLine) {
    TCHAR closer = 0;
    switch (**pLine) {
        case '(': closer = ')'; break;
        case '[': closer = ']'; break;
        case '{': closer = '}'; break;
        case '<': closer = '>'; break;
        default: return 0;
    }

    (*pLine)++;
    int inner = score(pLine);
    if (inner != 0) return inner;

    if (**pLine == closer) {
        (*pLine)++;
        return score(pLine);
    }

    switch (**pLine) {
        case ')': return 3;
        case ']': return 57;
        case '}': return 1197;
        case '>': return 25137;
    }

    return 0;
}

MCL_EXPORT(part1);
int part1(Object* input) {
    int sum = 0;
    for (int i = 0; i < input->cFields; i++) {
        LPTSTR line = input->pFields[i].pstrValue;

        sum += score(&line);
    }

    return sum;
}


// --- Part 2 ---

uint64_t score2(LPTSTR* pLine) {
    TCHAR closer = 0;
    int closer_val = 0;

    switch (**pLine) {
        case '(': closer = ')'; closer_val = 1; break;
        case '[': closer = ']'; closer_val = 2; break;
        case '{': closer = '}'; closer_val = 3; break;
        case '<': closer = '>'; closer_val = 4; break;
        default: return 0;
    }

    (*pLine)++;
    uint64_t inner = score2(pLine);

    // Inner pair was not closed, return invalid
    if (inner == -1) {
        return -1;
    }

    // End of line, accumulate closer values
    if (**pLine == 0) {
        return inner * 5 + closer_val;
    }

    // Pair successfully closed, check adjacent pair
    if (**pLine == closer) {
        (*pLine)++;
        return score2(pLine);
    }

    // Pair was not closed, return invalid
    return -1;
}

MCL_EXPORT(part2);
uint64_t part2(Object* input) {
    // Reserve an array to hold at least input->cFields scores
    uint64_t* scores = malloc(input->cFields * sizeof(uint64_t));
    int cScores = 0;

    // Record scores from valid but incomplete lines
    for (int i = 0; i < input->cFields; i++) {
        LPTSTR line = input->pFields[i].pstrValue;
        uint64_t score = score2(&line);
        if (score != -1) {
            scores[cScores++] = score;
        }
    }

    // Bubble sort the scores
    for (int i = cScores; i > 0; i--) {
        for (int j = 1; j < i; j++) {
            if (scores[j-1] > scores[j]) {
                uint64_t tmp_score = scores[j];
                scores[j] = scores[j-1];
                scores[j-1] = tmp_score;
            }
        }
    }

    // Pull out the median score
    uint64_t median_score = scores[cScores/2];

    // Free the array
    free(scores);

    // Return the median score
    return median_score;
}
