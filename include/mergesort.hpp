#ifndef GUARD_MERGESORT_HPP
#define GUARD_MERGESORT_HPP

#include <iostream>
#include <iterator>
#include <queue>

namespace
{
    template<class ForwardIter>
    void merge_ranges(ForwardIter b0, ForwardIter b1, ForwardIter e1)
    {
        std::queue<typename ForwardIter::value_type> vanished_from_r0;
        auto e0 = b1;
        while (b0 != e0)
        {
            if (vanished_from_r0.empty())
            {
                if (*b1 < *b0)
                {
                    vanished_from_r0.push(*b0);
                    *b0 = *b1;
                    b1++;
                }
            }
            else
            {
                if (*b1 < vanished_from_r0.front())
                {
                    vanished_from_r0.push(*b0);
                    *b0 = *b1;
                    b1++;
                }
                else
                {
                    vanished_from_r0.push(*b0);
                    *b0 = vanished_from_r0.front();
                    vanished_from_r0.pop();
                }
            }
            b0++;
        }
        while (b1 != e1 && !vanished_from_r0.empty())
        {
            if (*b1 < vanished_from_r0.front())
            {
                *b0 = *b1;
                b1++;
            }
            else
            {
                *b0 = vanished_from_r0.front();
                vanished_from_r0.pop();
            }
            b0++;
        }
        while (!vanished_from_r0.empty())
        {
            *b0 = vanished_from_r0.front();
            b0++;
            vanished_from_r0.pop();
        }
        std::copy(b1, e1, b0);
    }

    /**
     * The ranges must be adjacent.
     * The first range is [b0, b1) and the second one is [b1, e1)
    */
    template<class ForwardIter>
    void merge_ranges_in_place(ForwardIter b0, ForwardIter b1, ForwardIter e1)
    {
        // FIXME: This doesn't work

        auto old_start = b0;
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
            std::cerr << std::endl;
            for (auto it = old_start; it != b0; it++)
            {
                std::cerr << *it << " ";
            }
            std::cerr << "\t\t";
            for (auto it = b0; it != e0; it++)
            {
                std::cerr << *it << " ";
            }
            std::cerr << "\t\t";
            for (auto it = swapped_start; it != swapped_cur; it++)
            {
                std::cerr << *it << " ";
            }
            std::cerr << "\t\t";
            for (auto it = swapped_cur; it != b1; it++)
            {
                std::cerr << *it << " ";
            }
            std::cerr << "\t\t";
            for (auto it = b1; it != e1; it++)
            {
                std::cerr << *it << " ";
            }
            std::cerr << std::endl;

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
                if (*swapped_cur <= *b1)
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
                    std::iter_swap(b1, swapped_cur);
                    swapped_cur++;
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

template<class ForwardIter>
void mergesort(ForwardIter b, ForwardIter e,
               typename ForwardIter::difference_type size);


template<class ForwardIter>
void mergesort(ForwardIter b, ForwardIter e)
{
    auto size = std::distance(b, e);
    mergesort(b, e, size);
}

template<class ForwardIter>
void mergesort(ForwardIter b, ForwardIter e,
               typename ForwardIter::difference_type size)
{
    // If the range is empty or has one element, it's already sorted
    if (b == e || std::next(b, 1) == e)
    {
        return;
    }

    // Sort each halve of the range and merge them together
    // This is O(k) for random access iterators but O(n) for ForwardIter
    auto mid_point = std::next(b, size / 2);
    mergesort(b, mid_point, size / 2);
    mergesort(mid_point, e, size / 2 + size % 2);
    merge_ranges(b, mid_point, e);
}

#endif
