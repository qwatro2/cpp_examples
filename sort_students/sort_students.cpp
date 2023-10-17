#include "sort_students.h"

#include <tuple>

bool ComparerForDate(const Student& lhs, const Student& rhs) {
    auto l_compare_order =
        std::tie(lhs.birth_date.year, lhs.birth_date.month, lhs.birth_date.day, lhs.last_name, lhs.name);
    auto r_compare_order =
        std::tie(rhs.birth_date.year, rhs.birth_date.month, rhs.birth_date.day, rhs.last_name, rhs.name);

    return l_compare_order < r_compare_order;
}

bool ComparerForName(const Student& lhs, const Student& rhs) {
    auto l_compare_order =
        std::tie(lhs.last_name, lhs.name, lhs.birth_date.year, lhs.birth_date.month, lhs.birth_date.day);
    auto r_compare_order =
        std::tie(rhs.last_name, rhs.name, rhs.birth_date.year, rhs.birth_date.month, rhs.birth_date.day);

    return l_compare_order < r_compare_order;
}

void SortStudents(std::vector<Student>& students, SortKind sort_kind) {
    std::sort(students.begin(), students.end(), sort_kind == SortKind::Date ? ComparerForDate : ComparerForName);
}
