#include "admission.h"

bool ApplicantsComparer(const Applicant* lhs, const Applicant* rhs) {
    return std::tie(rhs->points, lhs->student.birth_date.year, lhs->student.birth_date.month,
                    lhs->student.birth_date.day, lhs->student.name) <
           std::tie(lhs->points, lhs->student.birth_date.year, lhs->student.birth_date.month,
                    lhs->student.birth_date.day, lhs->student.name);
}

bool StudentsComparer(const Student* lhs, const Student* rhs) {
    return std::tie(lhs->name, lhs->birth_date.year, lhs->birth_date.month, lhs->birth_date.day) <
           std::tie(rhs->name, rhs->birth_date.year, rhs->birth_date.month, rhs->birth_date.day);
}

AdmissionTable FillUniversities(const std::vector<University>& universities, const std::vector<Applicant>& applicants) {

    std::unordered_map<std::string, size_t> university_places_table;
    AdmissionTable admission_table;
    for (const auto& university : universities) {
        university_places_table[university.name] = university.max_students;
    }

    std::vector<const Applicant*> applicants_links;
    for (const auto& applicant : applicants) {
        applicants_links.push_back(&applicant);
    }

    std::sort(applicants_links.begin(), applicants_links.end(), ApplicantsComparer);

    for (const auto& applicant : applicants) {
        for (const auto& university : applicant.wish_list) {
            if (university_places_table[university] > admission_table[university].size()) {
                admission_table[university].push_back(&applicant.student);
                break;
            }
        }
    }

    for (auto& key_value : admission_table) {
        std::sort(key_value.second.begin(), key_value.second.end(), StudentsComparer);
    }

    return admission_table;
}
