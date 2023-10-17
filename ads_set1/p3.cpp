#include <utility>
#include <string>
#include <iostream>

std::pair<std::string, size_t> Decode(std::string& s, size_t start) {
    auto i = start;
    std::string result;

    while (i < s.length()) {
        auto c = s[i];

        if (c == ']') {
            break;
        }

        if ('0' <= c && c <= '9') {
            int iter_count = c - '0';
            ++i;

            if (c == '[') {
                auto pair = Decode(s, i + 1);
                i = pair.second;

                int j = 0;
                while (j < iter_count) {
                    result += pair.first;
                    ++j;
                }
            }
        } else {
            result += c;
            ++i;
        }
    }

    if (i < s.length()) {
        ++i;
    }

    return std::pair<std::string, size_t>(result, i);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::string input;
    getline(std::cin, input);

    std::cout << Decode(input, 0).first;
    return 0;
}