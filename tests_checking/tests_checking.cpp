#include "tests_checking.h"

#include "deque"

std::vector<std::string> StudentsOrder(const std::vector<StudentAction>& student_actions,
                                       const std::vector<size_t>& queries) {
    std::deque<size_t> students_numbers;

    for (size_t i = 0; i < student_actions.size(); ++i) {
        if (student_actions[i].side == Side::Top) {
            students_numbers.push_front(i);
        } else {
            students_numbers.push_back(i);
        }
    }

    std::vector<std::string> responses;
    responses.reserve(queries.size());

    for (auto query : queries) {
        responses.push_back(student_actions[students_numbers[query - 1]].name);
    }

    return responses;
}
