#include <functional>

template <class Iterator, class Comparator = std::less<typename std::iterator_traits<Iterator>::value_type>>
void Sort(Iterator begin, Iterator end, Comparator comparator = Comparator()) {
    for (Iterator i = begin; i < end; ++i) {
        for (Iterator j = i + 1; j < end; ++j) {
            if (!comparator(*i, *j)) {
                std::iter_swap(i, j);
            }
        }
    }
}
