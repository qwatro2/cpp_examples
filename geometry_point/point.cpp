#include "point.h"

#include "segment.h"
#include "vector.h"

int64_t geometry::Point::GetX() const {
    return x_coord_;
}

int64_t geometry::Point::GetY() const {
    return y_coord_;
}

void geometry::Point::SetX(int64_t new_x) {
    x_coord_ = new_x;
}

void geometry::Point::SetY(int64_t new_y) {
    y_coord_ = new_y;
}

geometry::Point &geometry::Point::Move(const geometry::Vector &vector) {
    x_coord_ += vector.GetX();
    y_coord_ += vector.GetY();
    return *this;
}

bool geometry::Point::ContainsPoint(const geometry::Point &point) const {
    return x_coord_ == point.GetX() && y_coord_ == point.GetY();
}

bool geometry::Point::CrossesSegment(const geometry::Segment &segment) const {
    // segment is AB, point is P
    auto vector_ap = *this - segment.GetStart();
    auto vector_bp = *this - segment.GetEnd();
    auto vector_ab = segment.GetEnd() - segment.GetStart();
    return ScalarMult(vector_ap, vector_ab) >= 0 && ScalarMult(vector_bp, vector_ab) <= 0 &&
           VectorMult(vector_ap, vector_ab) == 0;
}

geometry::Point *geometry::Point::Clone() const {
    return new Point(x_coord_, y_coord_);
}

geometry::Point::Point(int64_t x, int64_t y) : x_coord_(x), y_coord_(y) {
}

geometry::Vector geometry::Point::operator-(geometry::Point other) const {
    return geometry::Vector(x_coord_ - other.GetX(), y_coord_ - other.GetY());
}
