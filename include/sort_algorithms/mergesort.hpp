#ifndef GUARD_MERGESORT_HPP
#define GUARD_MERGESORT_HPP

#include <algorithm>
#include <deque>
#include <functional>
#include <iostream>
#include <iterator>

namespace
{
    template<class ForwardIter, class BinaryPred>
    void merge_ranges(ForwardIter b0, ForwardIter b1, ForwardIter e1,
                      BinaryPred cmp)
    {
        // This function is ugly. To avoid having to copy the range [b0, b1)
        // a std::deque<ForwardIter> vanished_from_r0 is created. Thanks to
        // that we reduce the storage cost (because ForwardIterator is
        // probably smaller than ForwardIterator::value_type at the extent of
        // some runtime performance.

        std::deque<ForwardIter> vanished_from_r0;
        auto e0 = b1;
        while (b0 != e0)
        {
            if (vanished_from_r0.empty())
            {
                if (cmp(*b1, *b0))
                {
                    std::iter_swap(b0, b1);
                    vanished_from_r0.push_back(b1);
                    b1++;
                }
            }
            else
            {
                if (cmp(*b1, *vanished_from_r0.front()))
                {
                    std::iter_swap(b0, b1);
                    vanished_from_r0.push_back(b1);
                    b1++;
                }
                else
                {
                    std::iter_swap(b0, vanished_from_r0.front());
                    vanished_from_r0.push_back(vanished_from_r0.front());
                    vanished_from_r0.pop_front();
                }
            }
            b0++;
        }

        while (b1 != e1 && !vanished_from_r0.empty())
        {
            // I suspect this could be logarithmic as vanished_from_r0 is
            // ordered in ascending order of dereference.
            auto rp = std::find(vanished_from_r0.begin(),
                                vanished_from_r0.end(), b0);

            if (cmp(*b1, *vanished_from_r0.front()))
            {
                std::iter_swap(b0, b1);
                *rp = b1;
                b1++;
            }
            else
            {
                std::iter_swap(b0, vanished_from_r0.front());
                *rp = vanished_from_r0.front();
                vanished_from_r0.pop_front();
            }
            b0++;
        }
        while (!vanished_from_r0.empty())
        {
            auto rp = std::find(vanished_from_r0.begin(),
                                vanished_from_r0.end(), b0);

            std::iter_swap(b0, vanished_from_r0.front());
            *rp = vanished_from_r0.front();
            vanished_from_r0.pop_front();
            b0++;
        }
        std::copy(b1, e1, b0);
    }
}

template<class ForwardIter, class BinaryPred>
void mergesort(ForwardIter b, ForwardIter e,
               typename ForwardIter::difference_type size,
               BinaryPred cmp)
{
    // If the range is empty or has one element, it's already sorted
    if (b == e || std::next(b, 1) == e)
    {
        return;
    }

    // Sort each halve of the range and merge them together
    // This is O(k) for random access iterators but O(n) for ForwardIter
    auto mid_point = std::next(b, size / 2);
    mergesort(b, mid_point, size / 2, cmp);
    mergesort(mid_point, e, size / 2 + size % 2, cmp);
    merge_ranges(b, mid_point, e, cmp);
}

template<class ForwardIter, class BinaryPred = std::less<>>
void mergesort(ForwardIter b, ForwardIter e, BinaryPred cmp = BinaryPred())
{
    auto size = std::distance(b, e);
    mergesort(b, e, size, cmp);
}

#endif
