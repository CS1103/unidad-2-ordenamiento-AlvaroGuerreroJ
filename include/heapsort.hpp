/**
 * Heapsort has two possible implementations depending on the type of the
 * iterators. It uses O(k) space if the iterators are random access and O(n)
 * space otherwise.
*/

#ifndef GUARD_HEAPSORT_HPP
#define GUARD_HEAPSORT_HPP

#include <algorithm>
#include <iterator>
#include <functional>

namespace
{
    template<class RandomIter, class BinaryPred>
    void max_heap(RandomIter b, RandomIter e,
                  typename RandomIter::difference_type cur_head,
                  BinaryPred cmp)
    {
        using iter_diff = typename RandomIter::difference_type;
        iter_diff max_diff = std::distance(b, e);
        auto max_pos_helper = [b, cmp, max_diff]
                              (iter_diff l, iter_diff r)
                              {
                                  if (r >= max_diff)
                                  {
                                      return l;
                                  }
                                  else if (cmp(b[l], b[r]))
                                  {
                                      return r;
                                  }
                                  else
                                  {
                                      return l;
                                  }
                              };
        iter_diff max_pos = max_pos_helper(cur_head, 2 * cur_head + 1);
        max_pos = max_pos_helper(max_pos, 2 * cur_head + 2);

        if (max_pos != cur_head)
        {
            std::iter_swap(b + cur_head, b + max_pos);
            max_heap(b, e, max_pos, cmp);
        }
    }

    template<class RandomIter, class BinaryPred>
    void build_max_heap(RandomIter b, RandomIter e, BinaryPred cmp)
    {
        if (b == e)
        {
            return;
        }

        auto pos = std::distance(b, e) - 1;
        do
        {
            max_heap(b, e, pos, cmp);
        } while (pos != 0 && (pos--, true));
    }

    template<class RandomIter, class BinaryPred>
    void delete_max(RandomIter b, RandomIter e, BinaryPred cmp)
    {
        std::iter_swap(b, e - 1);
        max_heap(b, e - 1, 0, cmp);
    }
}


template<class RandomIter, class BinaryPred = std::less<>>
void heapsort(RandomIter b, RandomIter e, BinaryPred cmp = BinaryPred())
{
    build_max_heap(b, e, cmp);

    for (auto it = e; it != b; it--)
    {
        delete_max(b, it, cmp);
    }
}

#endif
