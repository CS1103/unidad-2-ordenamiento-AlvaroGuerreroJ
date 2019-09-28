#ifndef GUARD_SHELLSORT_HPP
#define GUARD_SHELLSORT_HPP

#include <array>
#include <functional>

template<class RandomIter, class BinaryPred = std::less<>>
void shellsort(RandomIter b, RandomIter e, BinaryPred cmp = BinaryPred())
{
    using iter_diff = typename RandomIter::difference_type;

    // Sequence used retrieved from https://oeis.org/A102549
    std::array<iter_diff, 8> gaps = {
        701, 301, 132, 57, 23, 10, 4, 1
    };

    iter_diff iter_size = std::distance(b, e);

    for (iter_diff gap : gaps)
    {
        // Do insertion sort using current gap size

        for (iter_diff i = gap; i < iter_size; i++)
        {
            typename RandomIter::value_type temp = b[i];
            iter_diff j = i;
            for (; j >= gap && cmp(temp, b[j - gap]); j -= gap)
            {
                b[j] = b[j - gap];
            }
            b[j] = temp;
        }
    }
}

#endif
