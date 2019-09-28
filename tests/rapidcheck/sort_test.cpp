#include <algorithm>
#include <list>
#include <string>
#include <vector>

#include <rapidcheck.h>

#include <include/sort.hpp>

using std::list;
using std::string;
using std::vector;

int main()
{
    rc::check("mergesort with vector<int>",
              [](vector<int> v) {
                  vector<int> vc(v);
                  mergesort(v.begin(), v.end());
                  std::stable_sort(vc.begin(), vc.end());
                  RC_ASSERT(v == vc);
              });
    rc::check("mergesort with list<string>",
              [](list<string> v) {
                  list<string> vc(v);
                  mergesort(v.begin(), v.end());
                  vc.sort();
                  RC_ASSERT(v == vc);
              });
    rc::check("mergesort with vector<int> and custom cmp function",
              [](vector<int> v) {
                  vector<int> vc(v);
                  mergesort(v.begin(), v.end(), [](int l, int r){return r < l;});
                  std::sort(vc.rbegin(), vc.rend());
                  RC_ASSERT(v == vc);
              });

    rc::check("insertionsort with vector<string>",
              [](vector<string> v) {
                  vector<string> vc(v);
                  insertionsort(v.begin(), v.end());
                  std::stable_sort(vc.begin(), vc.end());
                  RC_ASSERT(v == vc);
              });
    rc::check("insertionsort with list<double>",
              [](list<double> v) {
                  list<double> vc(v);
                  insertionsort(v.begin(), v.end());
                  vc.sort();
                  RC_ASSERT(v == vc);
              });
    rc::check("insertionsort with vector<int> and custom cmp function",
              [](vector<int> v) {
                  vector<int> vc(v);
                  insertionsort(v.begin(), v.end(), [](int l, int r){return r < l;});
                  std::sort(vc.rbegin(), vc.rend());
                  RC_ASSERT(v == vc);
              });


    rc::check("quicksort with vector<int>",
              [](vector<int> v) {
                  vector<int> vc(v);
                  quicksort(v.begin(), v.end());
                  std::sort(vc.begin(), vc.end());
                  RC_ASSERT(v == vc);
              });
    rc::check("quicksort with vector<string>",
              [](vector<string> v) {
                  vector<string> vc(v);
                  quicksort(v.begin(), v.end());
                  std::sort(vc.begin(), vc.end());
                  RC_ASSERT(v == vc);
              });
    rc::check("quicksort with list<long>",
              [](list<long> v) {
                  list<long> vc(v);
                  quicksort(v.begin(), v.end());
                  vc.sort();
                  RC_ASSERT(v == vc);
              });
    rc::check("quicksort with vector<int> and custom cmp function",
              [](vector<int> v) {
                  vector<int> vc(v);
                  quicksort(v.begin(), v.end(), [](int l, int r){return r < l;});
                  std::sort(vc.rbegin(), vc.rend());
                  RC_ASSERT(v == vc);
              });


    rc::check("heapsort with vector<int>",
              [](vector<int> v) {
                  vector<int> vc(v);
                  heapsort(v.begin(), v.end());
                  std::sort(vc.begin(), vc.end());
                  RC_ASSERT(v == vc);
              });
    rc::check("heapsort with vector<string>",
              [](vector<string> v) {
                  vector<string> vc(v);
                  heapsort(v.begin(), v.end());
                  std::sort(vc.begin(), vc.end());
                  RC_ASSERT(v == vc);
              });
    rc::check("heapsort with vector<int> and custom cmp function",
              [](vector<int> v) {
                  vector<int> vc(v);
                  heapsort(v.begin(), v.end(), [](int l, int r){return r < l;});
                  std::sort(vc.rbegin(), vc.rend());
                  RC_ASSERT(v == vc);
              });

    rc::check("shellsort with vector<int>",
              [](vector<int> v) {
                  vector<int> vc(v);
                  shellsort(v.begin(), v.end());
                  std::sort(vc.begin(), vc.end());
                  RC_ASSERT(v == vc);
              });
    rc::check("shellsort with vector<string>",
              [](vector<string> v) {
                  vector<string> vc(v);
                  shellsort(v.begin(), v.end());
                  std::sort(vc.begin(), vc.end());
                  RC_ASSERT(v == vc);
              });
    rc::check("shellsort with vector<int> and custom cmp function",
              [](vector<int> v) {
                  vector<int> vc(v);
                  shellsort(v.begin(), v.end(), [](int l, int r){return r < l;});
                  std::sort(vc.rbegin(), vc.rend());
                  RC_ASSERT(v == vc);
              });
}
