#include "word2vec.h"

#include <vector>

int64_t ScalarMultiplication(const std::vector<int>& u, const std::vector<int>& v) {
    int64_t scalar_multiplication = 0;
    for (auto i = 0; i < u.size(); ++i) {
        scalar_multiplication += u[i] * v[i];
    }
    return scalar_multiplication;
}

std::vector<std::string> FindClosestWords(const std::vector<std::string>& words,
                                          const std::vector<std::vector<int>>& vectors) {
    if (vectors.size() < 2) {
        return {};
    }

    std::vector<std::string> closest_words{words[1]};
    auto maximum = ScalarMultiplication(vectors[0], vectors[1]);

    for (auto i = 2; i < vectors.size(); ++i) {
        auto current_maximum = ScalarMultiplication(vectors[0], vectors[i]);
        if (current_maximum > maximum) {
            maximum = current_maximum;
            closest_words.clear();
            closest_words.push_back(words[i]);
        } else if (current_maximum == maximum) {
            closest_words.push_back(words[i]);
        }
    }

    return closest_words;
}
