#include "chocolate.h"

bool CanBreakSlices(int height, int width, int slices_amount) {
    return (slices_amount % height == 0 && width - 1 >= slices_amount / height) ||
           (slices_amount % width == 0 && height - 1 >= slices_amount / width);
};