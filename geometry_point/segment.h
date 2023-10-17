#pragma once
#include "i_shape.h"
#include "point.h"

namespace geometry {
class Segment : public IShape {
private:
    Point start_;
    Point end_;

public:
    Segment() = default;

    Segment(Point, Point);

    Point GetStart() const;

    Point GetEnd() const;

    Segment& Move(const Vector& vector) override {
        start_ = Point(start_.GetX() + vector.GetX(), start_.GetY() + vector.GetY());
        end_ = Point(end_.GetX() + vector.GetX(), end_.GetY() + vector.GetY());
        return *this;
    };

    bool ContainsPoint(const Point& point) const override {
        return point.CrossesSegment(*this);
    }

    bool CrossesSegment(const Segment& segment) const override {
        return false;
    };

    Segment* Clone() const override {
        return nullptr;
    };
};
}  // namespace geometry
