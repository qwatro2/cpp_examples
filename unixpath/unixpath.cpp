#include "unixpath.h"

#include <vector>

std::vector<std::string_view> SplitStringView(std::string_view string_view, char delim) {
    std::vector<std::string_view> split_string_view;
    string_view.remove_prefix(std::min(string_view.find_first_not_of(" "), string_view.size()));

    while (!string_view.empty()) {
        auto first_delim = string_view.find(delim);
        split_string_view.push_back(string_view.substr(0, first_delim));

        if (string_view.find(delim) != string_view.npos) {
            string_view.remove_prefix(first_delim);
            string_view.remove_prefix(std::min(string_view.find_first_not_of(delim), string_view.size()));
        } else {
            string_view.remove_prefix(string_view.size());
        }
    }
    return split_string_view;
}

void Normalize(std::vector<std::string_view>& normalized_path, std::string_view path) {
    for (auto part : SplitStringView(path, '/')) {
        if (part == ".") {
        } else if (part == "..") {
            if (!normalized_path.empty()) {
                normalized_path.pop_back();
            }
        } else {
            if (!part.empty()) {
                normalized_path.push_back(part);
            }
        }
    }
}

std::string NormalizePath(std::string_view current_working_dir, std::string_view path) {
    std::vector<std::string_view> normalized_path_vector;

    if (!path.starts_with('/')) {
        Normalize(normalized_path_vector, current_working_dir);
    }
    Normalize(normalized_path_vector, path);

    std::string normalized_path = "/";
    for (auto part : normalized_path_vector) {
        normalized_path += std::string(part) + "/";
    }

    if (!normalized_path_vector.empty()) {
        normalized_path.pop_back();
    }

    return normalized_path;
}
