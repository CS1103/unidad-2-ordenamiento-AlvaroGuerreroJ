#include <algorithm>
#include <vector>

#include <rapidcheck.h>

#include <sort.hpp>

using std::vector;

int main()
{
    rc::check("Must sort the same way as std::sort",
              [](vector<int> v) {
        vector<int> vc(v);
        merge_sort(v.begin(), v.end());
        std::sort(vc.begin(), vc.end());
        RC_ASSERT(v == vc);
    });
}
