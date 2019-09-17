#include <iterator>

namespace
{
    /**
     * The ranges must be adjacent.
     * The first range is [b0, b1) and the second one is [b1, e1)
    */
    template<typename ForwardIter>
    void merge_ranges(ForwardIter b0, ForwardIter b1, ForwardIter e1)
    {
        // If any of the ranges is exhausted, then it's already merged
        ForwardIter e0 = b1;
        if (b0 == e0 || b1 == e1)
        {
            return;
        }

        ForwardIter const swapped_start = b1;
        ForwardIter swapped_cur = swapped_start;
        while (true)
        {
            // First range exhausted
            if (b0 == e0)
            {
                merge_ranges(swapped_start, swapped_cur, b1);
                merge_ranges(swapped_start, b1, e1);
                return;
            }
            // Second range exhausted
            if (b1 == e1)
            {
                merge_ranges(swapped_start, swapped_cur, b1);
                merge_ranges(b0, swapped_start, b1);
                return;
            }

            if (swapped_cur != b1)
            {
                if (*swapped_cur < *b1)
                {
                    std::iter_swap(swapped_cur, b0);
                    swapped_cur++;
                    if (swapped_cur == b1)
                    {
                        swapped_cur = swapped_start;
                    }
                }
                else
                {
                    std::iter_swap(b0, b1);
                    b1++;
                }
            }
            else
            {
                if (*b1 < *b0)
                {
                    std::iter_swap(b0, b1);
                    b1++;
                }
            }
            b0++;
        }
    }
}


template<typename ForwardIter>
void merge_sort(ForwardIter b, ForwardIter e)
{
    // If the range is empty, it's already sorted
    if (b == e)
    {
        return;
    }
    // If the range has only one element, it's already sorted
    if (std::next(b, 1) == e)
    {
        return;
    }

    // Sort each halve of the range and merge them together
    // This is O(k) for random access iterators but O(n) for ForwardIter
    auto mid_point = std::next(b, std::distance(b, e) / 2);
    merge_sort(b, mid_point);
    merge_sort(mid_point, e);
    merge_ranges(b, mid_point, e);
}
