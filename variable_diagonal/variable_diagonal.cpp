#include "variable_diagonal.h"

int** BuildDiagonalArray(size_t lines, size_t columns) {
    int** table = new int*[lines];

    for (int i = 0; i < lines; ++i) {
        table[i] = new int[columns];
    }

    table[0][0] = 0;

    if (lines >= columns) {
        size_t k = lines - columns;
        for (int j = 1; j < columns; ++j) {
            table[0][j] = table[0][j - 1] + j;
        }
        for (size_t t = 0; t < k; ++t) {
            table[t + 1][columns - 1] = static_cast<int>(table[t][columns - 1] + lines);
        }
        for (int t = 0; t < columns - 1; ++t) {
            table[k + 1 + t][columns - 1] = static_cast<int>(table[k + t][columns - 1] + columns - t);
        }
    } else {
        size_t k = columns - lines;
        for (int j = 1; j < lines; ++j) {
            table[0][j] = table[0][j - 1] + j;
        }
        for (int t = 0; t < k; ++t) {
            table[0][lines + t] = static_cast<int>(table[0][lines + t - 1] + lines);
        }
        for (int t = 0; t < lines - 1; ++t) {
            table[t + 1][columns - 1] = static_cast<int>(table[t][columns - 1] + lines - t);
        }
    }

    for (int i = 1; i < lines; ++i) {
        for (int j = 0; j < columns - 1; ++j) {
            table[i][j] = table[i - 1][j + 1] + 1;
        }
    }

    return table;
}