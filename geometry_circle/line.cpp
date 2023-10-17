#include "line.h"

#include "cmath"
#include "point.h"
#include "segment.h"

geometry::Line::Line(Point start, Point end) : start_(start), end_(end) {
}

double geometry::Line::Distance(geometry::Point point) const {
    // P is point
    // let P1 in line (start_x + t * line_vector_x, start_y + t * line_vector_y)
    // PP1 { start_x + t * line_vector_x - p_x , start_y + t * line_vector_y - p_y}
    // PP1 is ortogonal to line <=> (line_vector, PP1) = 0

    auto line_vector = end_ - start_;

    auto t =
        (line_vector.GetX() * (point.GetX() - start_.GetX()) + line_vector.GetY() * (point.GetY() - start_.GetY())) /
        static_cast<long double>(line_vector.GetX() * line_vector.GetX() + line_vector.GetY() * line_vector.GetY());

    return static_cast<double>(std::hypot(start_.GetX() + t * line_vector.GetX() - point.GetX(),
                                          start_.GetY() + t * line_vector.GetY() - point.GetY()));
}

geometry::Line& geometry::Line::Move(const geometry::Vector& vector) {
    start_ = Point(start_.GetX() + vector.GetX(), start_.GetY() + vector.GetY());
    end_ = Point(end_.GetX() + vector.GetX(), end_.GetY() + vector.GetY());
    return *this;
}

bool geometry::Line::ContainsPoint(const geometry::Point& point) const {
    return GetA() * point.GetX() + GetB() * point.GetY() + GetC() == 0;
}

bool geometry::Line::CrossesSegment(const geometry::Segment& segment) const {
    return (GetA() * segment.GetStart().GetX() + GetB() * segment.GetStart().GetY() + GetC() >= 0 &&
            GetA() * segment.GetEnd().GetX() + GetB() * segment.GetEnd().GetY() + GetC() <= 0) ||
           (GetA() * segment.GetStart().GetX() + GetB() * segment.GetStart().GetY() + GetC() <= 0 &&
            GetA() * segment.GetEnd().GetX() + GetB() * segment.GetEnd().GetY() + GetC() >= 0);
}

geometry::Line* geometry::Line::Clone() const {
    return new Line(start_, end_);
}

int64_t geometry::Line::GetA() const {
    return start_.GetY() - end_.GetY();
}

int64_t geometry::Line::GetB() const {
    return end_.GetX() - start_.GetX();
}

int64_t geometry::Line::GetC() const {
    return start_.GetX() * end_.GetY() - start_.GetY() * end_.GetX();
}
