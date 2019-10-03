#ifndef GUARD_SORT_HPP
#define GUARD_SORT_HPP

#include <iterator>

#include "sort_algorithms/insertionsort.hpp"
#include "sort_algorithms/heapsort.hpp"
#include "sort_algorithms/mergesort.hpp"
#include "sort_algorithms/quicksort.hpp"
#include "sort_algorithms/shellsort.hpp"

template<class Iter>
void sort(Iter b, Iter e)
{
    using tag = typename std::iterator_traits<Iter>::iterator_category;
    sort(b, e, tag());
}

template<class RandomIter>
void sort(RandomIter b, RandomIter e, std::random_access_iterator_tag)
{
    heapsort(b, e);
}

template<class BidirIter>
void sort(BidirIter b, BidirIter e, std::bidirectional_iterator_tag)
{
    quicksort(b, e);
}

template<class ForwardIter>
void sort(ForwardIter b, ForwardIter e, std::forward_iterator_tag)
{
    mergesort(b, e);
}

#endif
