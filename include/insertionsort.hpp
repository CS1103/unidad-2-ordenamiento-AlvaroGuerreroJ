#ifndef GUARD_INSERTIONSORT_HPP
#define GUARD_INSERTIONSORT_HPP

#include <iterator>

template<class BidirectionalIter, class BinaryPred = std::less<>>
void insertionsort(BidirectionalIter b, BidirectionalIter e,
                   BinaryPred cmp = BinaryPred())
{
    if (b == e || std::next(b, 1) == e)
    {
        return;
    }

    // Invariant: The array from [b, unsorted_start) is sorted
    for (auto unsorted_start = std::next(b, 1); unsorted_start != e;
         unsorted_start++)
    {
        for (auto it = unsorted_start; it != b && cmp(*it, *std::next(it, -1)); it--)
        {
            std::iter_swap(it, std::next(it, -1));
        }
    }
}

#endif
