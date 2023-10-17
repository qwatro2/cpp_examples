#include "ray.h"

#include "line.h"
#include "segment.h"
#include "vector.h"

namespace geometry {
Ray::Ray(Point first, Point second) : start_(first), end_(second) {
}

Ray& Ray::Move(const Vector& vector) {
    start_.Move(vector);
    end_.Move(vector);
    return *this;
}

bool Ray::ContainsPoint(const Point& point) const {
    auto line = Line(start_, end_);
    auto is_in_line = line.ContainsPoint(point);

    if (!is_in_line) {
        return false;
    }

    return ScalarMult(end_ - start_, point - start_) >= 0;
}

bool Ray::CrossesSegment(const Segment& segment) const {
    auto line = Line(start_, end_);
    auto is_line_crosses = line.CrossesSegment(segment);

    if (!is_line_crosses) {
        return false;
    }

    if (ContainsPoint(segment.GetStart()) || ContainsPoint(segment.GetEnd())) {
        return true;
    }

    return ScalarMult(end_ - start_, segment.GetStart() - start_) >= 0;
}

Ray* Ray::Clone() const {
    return new Ray(start_, end_);
}

Point Ray::GetStart() const {
    return start_;
}

Point Ray::GetEnd() const {
    return end_;
}
}  // namespace geometry