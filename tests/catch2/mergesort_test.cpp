#include <list>
#include <vector>
#include <catch2/catch.hpp>

#include <sort.hpp>

using std::list;
using std::vector;

TEST_CASE("Merge sort")
{
    SECTION("Sort a vector")
    {
        vector<int> v0 = {8, 2, 4, -2, 0, 2, 2, 99};
        mergesort(v0.begin(), v0.end());
        CHECK(v0 == vector<int>{-2, 0, 2, 2, 2, 4, 8, 99});
    }

    SECTION("Sort a list")
    {
        list<int> v0 = {8, 2, 4, -2, 0, 2, 2, 99};
        mergesort(v0.begin(), v0.end());
        CHECK(v0 == list<int>{-2, 0, 2, 2, 2, 4, 8, 99});
    }
}
