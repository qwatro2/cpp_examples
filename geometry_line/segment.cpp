#include "segment.h"

#include "point.h"

geometry::Segment::Segment(geometry::Point start, geometry::Point end) : start_(start), end_(end) {
}

geometry::Point geometry::Segment::GetStart() const {
    return start_;
}

geometry::Point geometry::Segment::GetEnd() const {
    return end_;
}
