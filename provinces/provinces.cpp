#include "provinces.h"

int64_t CountPassports(const std::vector<int>& provinces) {
    std::multiset<int64_t> multiset_provinces(provinces.begin(), provinces.end());
    int64_t passport_counter = 0;

    while (multiset_provinces.size() > 1) {
        auto min1 = multiset_provinces.extract(multiset_provinces.begin()).value();
        auto min2 = multiset_provinces.extract(multiset_provinces.begin()).value();
        multiset_provinces.insert(min1 + min2);
        passport_counter += min1 + min2;
    }

    return passport_counter;
}
