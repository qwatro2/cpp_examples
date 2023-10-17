#include "segment.h"

#include "point.h"

namespace geometry {
int64_t Area(const Vector& ab, const Vector& ac) {
    return ab.GetX() * ac.GetY() - ab.GetY() * ac.GetX();
}

bool BoundingBoxCheck(int64_t a, int64_t b, int64_t c, int64_t d) {
    if (a > b) {
        std::swap(a, b);
    }
    if (c > d) {
        std::swap(c, d);
    }

    return std::max(a, c) <= std::min(b, d);
}

Segment::Segment(Point start, Point end) : start_(start), end_(end) {
}

Point Segment::GetStart() const {
    return start_;
}

Point Segment::GetEnd() const {
    return end_;
}

double Segment::Distance(Point point) const {
    // найдем основание перпендикуляра на прямую, содержащую отрезок
    auto line_vector = end_ - start_;
    auto t =
        (line_vector.GetX() * (point.GetX() - start_.GetX()) + line_vector.GetY() * (point.GetY() - start_.GetY())) /
        static_cast<long double>(line_vector.GetX() * line_vector.GetX() + line_vector.GetY() * line_vector.GetY());

    if (t < 0) {
        return Length(start_ - point);
    }

    if (t > 1) {
        return Length(end_ - point);
    }

    return static_cast<double>(std::hypot(start_.GetX() + t * line_vector.GetX() - point.GetX(),
                                          start_.GetY() + t * line_vector.GetY() - point.GetY()));
}

bool Segment::Degenerate() const {
    return start_.GetX() == end_.GetX() && start_.GetY() == end_.GetY();
}

bool Segment::ContainsPoint(const Point& point) const {
    return point.CrossesSegment(*this);
}

bool Segment::CrossesSegment(const Segment& segment) const {
    return BoundingBoxCheck(start_.GetX(), end_.GetX(), segment.GetStart().GetX(), segment.GetEnd().GetX()) &&
           BoundingBoxCheck(start_.GetY(), end_.GetY(), segment.GetStart().GetY(), segment.GetEnd().GetY()) &&
           Area(end_ - start_, segment.GetStart() - start_) * Area(end_ - start_, segment.GetEnd() - start_) <= 0 &&
           Area(segment.GetEnd() - segment.GetStart(), start_ - segment.GetStart()) *
                   Area(segment.GetEnd() - segment.GetStart(), end_ - segment.GetStart()) <=
               0;
}

Segment* Segment::Clone() const {
    return new Segment(start_, end_);
}

Segment& Segment::Move(const geometry::Vector& vector) {
    start_.Move(vector);
    end_.Move(vector);
    return *this;
}
}  // namespace geometry