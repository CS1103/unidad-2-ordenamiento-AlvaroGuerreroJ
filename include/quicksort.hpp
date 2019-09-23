#ifndef GUARD_QUICKSORT_HPP
#define GUARD_QUICKSORT_HPP

#include <algorithm>
#include <functional>
#include <iterator>

#include "insertionsort.hpp"

template<class BidirectionalIter, class BinaryPred = std::less<>>
void quicksort(BidirectionalIter b, BidirectionalIter e,
               BinaryPred cmp = BinaryPred())
{
    // If the list is less than 8 elements, it's sorted using insertion sort
    using iter_diff = typename BidirectionalIter::difference_type;
    iter_diff const insertionsort_threshold = 8;
    iter_diff count = 0;
    for (auto it = b; it != e && count < insertionsort_threshold; it++)
    {
        count++;
    }
    if (count < insertionsort_threshold)
    {
        insertionsort(b, e);
        return;
    }
    // If got here, the range to be sorted is at least of size 8

    BidirectionalIter gb = b;
    BidirectionalIter ge = std::next(e, -1);

    // Choose as pivot the median of the first, first + 1, last and last - 1 values
    typename BidirectionalIter::value_type const pivot = [gb, ge, cmp](){
        auto gb_p1 = std::next(gb, 1);
        auto ge_m1 = std::next(ge, -1);

        // Sorting network of size 4
        if (cmp(*gb_p1, *gb))
        {
            std::iter_swap(gb, gb_p1);
        }
        if (cmp(*ge, *ge_m1))
        {
            std::iter_swap(ge_m1, ge);
        }

        if (cmp(*ge_m1, *gb))
        {
            std::iter_swap(gb, ge_m1);
        }
        if (cmp(*ge, *gb_p1))
        {
            std::iter_swap(gb_p1, ge);
        }

        if (cmp(*ge_m1, *gb_p1))
        {
            std::iter_swap(gb_p1, ge_m1);
        }

        return *gb_p1;
    }();

    // At this point is true that: *gb <= pivot and pivot <= *ge

    // if (*ge == pivot)
    // {
    //     BidirectionalIter new_ge = std::find_if(b, e,
    //                                             [pivot](typename BidirectionalIter::value_type v)
    //                                             {
    //                                                 return pivot < v;
    //                                             });
    //     // If this is true, then the pivot was the largest element in the container
    //     if (new_ge == e)
    //     {
    //         quicksort(b, ge);
    //         return;
    //     }
    //     std::iter_swap(new_ge, ge);
    // }

    // Invariant: *gb <= pivot // and pivot < *ge
    while (true)
    {
        while (gb != ge && !cmp(pivot, *gb))
        {
            gb++;
        }
        while (gb != ge && cmp(pivot, *ge))
        {
            ge--;
        }
        if (gb == ge)
        {
            BidirectionalIter partition_point = gb;
            quicksort(b, partition_point, cmp);
            quicksort(partition_point, e, cmp);
            return;
        }
        std::iter_swap(gb, ge);
    }
}

#endif