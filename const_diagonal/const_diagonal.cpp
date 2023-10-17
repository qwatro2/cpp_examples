#include "const_diagonal.h"

void BuildDiagonalArray(TableType table) {

    table[0][0] = 0;

    if (LINES >= COLUMNS) {
        for (int j = 1; j < COLUMNS; ++j) {
            table[0][j] = table[0][j - 1] + j;
        }
        int k = LINES - COLUMNS;
        for (int t = 0; t < k; ++t) {
            table[t + 1][COLUMNS - 1] = table[t][COLUMNS - 1] + k + COLUMNS;
        }
        for (int t = 0; t < COLUMNS - 1; ++t) {
            table[k + 1 + t][COLUMNS - 1] = table[k + t][COLUMNS - 1] + COLUMNS - t;
        }
    } else {
        int k = COLUMNS - LINES;
        for (int j = 1; j < LINES; ++j) {
            table[0][j] = table[0][j - 1] + j;
        }
        for (int t = 0; t < k; ++t) {
            table[0][LINES + t] = table[0][LINES + t - 1] + LINES;
        }
        for (int t = 0; t < LINES - 1; ++t) {
            table[t + 1][COLUMNS - 1] = table[t][COLUMNS - 1] + LINES - t;
        }
    }

    for (int i = 1; i < LINES; ++i) {
        for (int j = 0; j < COLUMNS - 1; ++j) {
            table[i][j] = table[i - 1][j + 1] + 1;
        }
    }
}
