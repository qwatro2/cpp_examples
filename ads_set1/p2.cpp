#include <algorithm>
#include <set>
#include <vector>
#include <iostream>

size_t CountArrayRotations(std::vector<int>& array) {
    auto n = array.size();

    int max_d = -1;
    size_t max_d_count = 0;

    std::set<std::vector<int>> set;

    for (auto start = 0; start < n; ++start) {
        auto d_count = 0;
        
        std::vector<int> current;

        for (int i = 0; i < n; ++i) {
            current.push_back(array[(start + i) % n]);

            if (array[(start + i) % n] != array[i]) {
                ++d_count;
            }
        }
        
        if (set.find(current) != set.end()) {
            continue;
        }

        set.insert(current);

        if (d_count == max_d) {
            ++max_d_count;
        } else if (d_count > max_d) {
            max_d_count = 1;
            max_d = d_count;
        }
    }

    return max_d_count;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    size_t size;
    int current;
    std::cin >> size;
    std::vector<int> array;
    for (size_t i = 0; i < size; ++i) {
        std::cin >> current;
        array.push_back(current);
    }

    // for (auto i : array) {
    //     std::cout << i << '\t';
    // }
    // std::cout << '\n';

    std::cout << CountArrayRotations(array);
    return 0;
}
