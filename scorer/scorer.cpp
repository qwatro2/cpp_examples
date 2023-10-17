#include "scorer.h"

struct TaskProps {
    bool is_checked = false;
    bool is_merge_request_closed = true;
    time_t checked_last_change = -1;
    time_t merge_last_change = -1;
};

ScoreTable GetScoredStudents(const Events& events, time_t score_time) {

    if (events.empty()) {
        return {};
    }

    ScoreTable score_table;
    std::map<StudentName, std::map<TaskName, TaskProps>> student_task_props_table;

    for (const auto& event : events) {
        if (event.time > score_time) {
            continue;
        }

        auto current_task = &student_task_props_table[event.student_name][event.task_name];

        switch (event.event_type) {
            case EventType::CheckFailed:
                if (event.time > current_task->checked_last_change) {
                    current_task->is_checked = false;
                    current_task->checked_last_change = event.time;
                }
                break;
            case EventType::CheckSuccess:
                if (event.time > current_task->checked_last_change) {
                    current_task->is_checked = true;
                    current_task->checked_last_change = event.time;
                }
                break;
            case EventType::MergeRequestOpen:
                if (event.time > current_task->checked_last_change) {
                    current_task->is_merge_request_closed = false;
                    current_task->merge_last_change = event.time;
                }
                break;
            case EventType::MergeRequestClosed:
                if (event.time > current_task->checked_last_change) {
                    current_task->is_merge_request_closed = true;
                    current_task->merge_last_change = event.time;
                }
                break;
        }
    }

    for (const auto& student_map : student_task_props_table) {
        for (const auto& task_name_task_props : student_task_props_table[student_map.first]) {
            if (task_name_task_props.second.is_checked && task_name_task_props.second.is_merge_request_closed) {
                score_table[student_map.first].insert(task_name_task_props.first);
            }
        }
    }

    return score_table;
}
