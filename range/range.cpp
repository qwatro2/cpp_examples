#include "range.h"

std::vector<int> Range(int from, int to, int step) {
    std::vector<int> range;

    auto checker = [to, step](int i) { return step > 0 ? i < to : step < 0 && i > to; };

    for (int i = from; checker(i); i += step) {
        range.push_back(i);
    }

    return range;
}
