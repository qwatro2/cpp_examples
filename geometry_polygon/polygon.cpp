#include "polygon.h"

#include "line.h"
#include "segment.h"

namespace geometry {

bool operator==(const Point& lhs, const Point& rhs) {
    return lhs.GetX() == rhs.GetX() && lhs.GetY() == rhs.GetY();
}

Polygon::Polygon(std::vector<Point> points) : points_(points), num_points_(points.size()) {
}

Polygon& Polygon::Move(const Vector& vector) {
    for (auto& point : points_) {
        point.Move(vector);
    }

    return *this;
}

bool Polygon::ContainsPoint(const Point& point) const {
    auto line = Line(point, Point(point.GetX() + 1, point.GetY() + 4));
    size_t intersection_counter = 0;

    const auto min_double = 10e-9;

    for (auto i = 0; i < num_points_; ++i) {
        auto current_segment = Segment(points_[i], points_[(i + 1) % num_points_]);

        if (current_segment.ContainsPoint(point)) {
            return true;
        }

        if (line.ContainsPoint(current_segment.GetStart()) && line.ContainsPoint(current_segment.GetEnd())) {
            if (std::max(current_segment.GetStart().GetX(), current_segment.GetEnd().GetX()) < point.GetX()) {
                continue;
            }
            ++intersection_counter;
            continue;
        }

        if (line.CrossesSegment(current_segment) && (!line.ContainsPoint(current_segment.GetStart()))) {
            auto a = static_cast<double>(current_segment.GetStart().GetX());
            auto b = static_cast<double>(current_segment.GetStart().GetY());
            auto c = static_cast<double>(current_segment.GetEnd().GetX());
            auto d = static_cast<double>(current_segment.GetEnd().GetY());
            auto x = static_cast<double>(point.GetX());
            auto y = static_cast<double>(point.GetY());
            // прямая y = 4x + m
            auto m = y - x * 4;

            if (std::abs(a - c) < min_double) {
                if (a - x > min_double) {
                    ++intersection_counter;
                }
                continue;
            }

            auto x_inters = (a * (d - m) - (b + m) * c) / (4 * a - 4 * c - b + d);
            auto y_inters = 4 * x_inters + m;

            if (x_inters - x > min_double && y_inters - y > min_double) {
                ++intersection_counter;
            }
        }
    }

    return intersection_counter % 2 == 1;
}

bool Polygon::CrossesSegment(const Segment& segment) const {
    for (auto i = 0; i < num_points_; ++i) {
        auto current_segment = Segment(points_[i], points_[(i + 1) % num_points_]);
        if (segment.CrossesSegment(current_segment)) {
            return true;
        }
    }

    return false;
}

Polygon* Polygon::Clone() const {
    return new Polygon(points_);
}

}  // namespace geometry