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
    if (x_coord_ >= std::min(segment.GetStart().x_coord_, segment.GetEnd().x_coord_) &&
        x_coord_ <= std::max(segment.GetStart().x_coord_, segment.GetEnd().x_coord_) &&
        y_coord_ >= std::min(segment.GetStart().y_coord_, segment.GetEnd().y_coord_) &&
        y_coord_ <= std::max(segment.GetStart().y_coord_, segment.GetEnd().y_coord_)) {

        if (segment.GetEnd().x_coord_ == segment.GetStart().x_coord_) {
            return (x_coord_ == segment.GetStart().x_coord_);
        }

        auto coefficient_numer = segment.GetEnd().y_coord_ - segment.GetStart().y_coord_;
        auto coefficient_denom = segment.GetEnd().x_coord_ - segment.GetStart().x_coord_;
        auto free_numer =
            segment.GetStart().y_coord_ * coefficient_denom - coefficient_numer * segment.GetStart().x_coord_;

        return y_coord_ * coefficient_denom * coefficient_denom ==
               coefficient_numer * coefficient_denom * x_coord_ + free_numer * coefficient_denom;
    }

    return false;
}

geometry::Point *geometry::Point::Clone() const {
    return new Point(x_coord_, y_coord_);
}

geometry::Point::Point(int64_t x, int64_t y) : x_coord_(x), y_coord_(y) {
}

geometry::Vector geometry::Point::operator-(geometry::Point other) const {
    return geometry::Vector(x_coord_ - other.GetX(), y_coord_ - other.GetY());
}
