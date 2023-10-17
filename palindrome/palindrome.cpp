#include "palindrome.h"

bool IsPalindrome(const std::string& str) {

    if (str.empty()) {
        return true;
    }

    auto left = str.begin();
    auto right = str.end() - 1;
    while (left <= right) {
        if (*left == ' ') {
            ++left;
        } else if (*right == ' ') {
            --right;
        } else if (*left == *right) {
            ++left;
            if (right == str.begin()) {
                return true;
            }
            --right;
        } else {
            return false;
        }
    }

    return true;
}
