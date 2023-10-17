#include "circle.h"

#include "cmath"
#include "segment.h"
#include "vector.h"

namespace geometry {

Circle::Circle(Point point, int64_t radius) : centre_(point), radius_(radius) {
}

Circle& Circle::Move(const Vector& vector) {
    centre_.Move(vector);
    return *this;
}

Circle* Circle::Clone() const {
    return new Circle(centre_, radius_);
}

int64_t Circle::GetRadius() const {
    return radius_;
}

Point Circle::GetCenter() const {
    return centre_;
}

bool Circle::ContainsPoint(const Point& point) const {
    auto moved_x = point.GetX() - centre_.GetX();
    auto moved_y = point.GetY() - centre_.GetY();

    return moved_x * moved_x + moved_y * moved_y <= radius_ * radius_;
}

bool Circle::CrossesSegment(const Segment& segment) const {

    auto x1 = static_cast<double>(segment.GetStart().GetX());
    auto y1 = static_cast<double>(segment.GetStart().GetY());
    auto x2 = static_cast<double>(segment.GetEnd().GetX());
    auto y2 = static_cast<double>(segment.GetEnd().GetY());

    auto centre_x = static_cast<double>(centre_.GetX());
    auto centre_y = static_cast<double>(centre_.GetY());
    auto r = static_cast<double>(radius_);

    auto vector_x = x2 - x1;
    auto vector_y = y2 - y1;

    // ур-ние на пересечение ax^2 + bx + c = 0
    auto a = vector_x * vector_x + vector_y * vector_y;
    auto b = 2 * (vector_x * (x1 - centre_x) + vector_y * (y1 - centre_y));
    auto c =
        centre_x * centre_x + centre_y * centre_y + x1 * x1 + y1 * y1 - 2 * (centre_x * x1 + centre_y * y1) - r * r;

    auto discriminant = b * b - 4 * a * c;

    auto t_check = [](double t) { return 0 <= t && t <= 1; };

    if (a == 0) {
        if (b == 0) {
            return c == 0;
        }

        return t_check(-static_cast<double>(c) / static_cast<double>(b));
    }

    return t_check((-static_cast<double>(b) + std::sqrt(discriminant)) / (2 * static_cast<double>(a))) ||
           t_check((-static_cast<double>(b) - std::sqrt(discriminant)) / (2 * static_cast<double>(a)));
}

}  // namespace geometry