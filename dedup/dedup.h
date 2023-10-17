#pragma once

#include <memory>
#include <string>
#include <vector>

#include "map"

using std::string;

template <class T>
std::vector<std::unique_ptr<T>> Duplicate(const std::vector<std::shared_ptr<T>>& items) {
    std::vector<std::unique_ptr<T>> result;

    for (const auto& item : items) {
        result.emplace_back(std::make_unique<T>(*item));
    }

    return result;
}

template <class T>
std::vector<std::shared_ptr<T>> DeDuplicate(const std::vector<std::unique_ptr<T>>& items) {
    std::map<T, std::shared_ptr<T>> first_entrance;
    std::vector<std::shared_ptr<T>> result;

    for (const auto& item : items) {
        if (!first_entrance.contains(*item)) {
            first_entrance[*item] = std::make_shared<T>(*item);
        }

        result.push_back(first_entrance[*item]);
    }

    return result;
}
