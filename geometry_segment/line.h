#ifndef GEOMETRYCLASSES__LINE_H_
#define GEOMETRYCLASSES__LINE_H_

#include "i_shape.h"
#include "point.h"

namespace geometry {
class Line : public IShape {
private:
    Point start_;
    Point end_;

public:
    Line() = default;

    int64_t GetA() const;

    int64_t GetB() const;

    int64_t GetC() const;

    Line(Point start, Point end);

    double Distance(Point) const;

    Line& Move(const Vector& vector) override;

    bool ContainsPoint(const Point& point) const override;

    bool CrossesSegment(const Segment& segment) const override;

    Line* Clone() const override;
};
}  // namespace geometry

#endif  // GEOMETRYCLASSES__LINE_H_
