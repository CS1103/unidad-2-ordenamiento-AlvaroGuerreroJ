#include <algorithm>
#include <iostream>
#include <fstream>
#include <iterator>
#include <list>
#include <string>
#include <utility>
#include <vector>

#include <lib/prettyprint.hpp>

#include <include/read_csv.hpp>
#include <include/sort.hpp>

#include "Criterion.hpp"

using std::cout;
using std::endl;
using std::find;
using std::list;
using std::next;
using std::ofstream;
using std::string;
using std::pair;
using std::vector;

// TODO: Where should I put this function?
template<class ForwardIter>
ofstream& write_row(ForwardIter b, ForwardIter e, ofstream& out)
{
    while (b != e)
    {
        if (find(b->begin(), b->end(), ',') != b->end())
        {
            out << "\"";
            out << *b;
            out << "\"";
        }
        else
        {
            out << *b;
        }

        // Don't write the comma after the last column
        if (next(b, 1) != e)
        {
            out << ",";
        }

        b++;
    }

    out << endl;

    return out;
}

int main()
{
    using row = vector<string>;
    using data_storage = vector<row>;
    string filename = "commodity_trade_statistics_data.csv";
    data_storage data = read_csv<vector>(filename);

    // The first row are the headers, so we remove them.
    // TODO: This is O(n).
    row headers = data.front();
    data.erase(data.begin());

    vector<Criterion> criteria = {
        {"Criterion_1", headers, {"trade_usd"}},
        {"Criterion_2", headers, {"country_or_area", "year",
                                  "flow", "commodity", "trade_usd"}}
    };

    typedef void (sort_algorithm)(data_storage::iterator,
                                  data_storage::iterator, Criterion);
    vector<pair<string, sort_algorithm*>> names_and_algorithms {
        {"heapsort", heapsort<data_storage::iterator, Criterion>},
        {"mergesort", mergesort<data_storage::iterator, Criterion>},
        {"quicksort", quicksort<data_storage::iterator, Criterion>},
        {"shellsort", shellsort<data_storage::iterator, Criterion>}
    };

    for (auto const& pns : names_and_algorithms)
    {
        for (Criterion const& cr : criteria)
        {
            cout << "Doing " << pns.first << " with " << cr.get_name() << endl;

            // Because the sorting algorithms work in place, we must create a
            // copy of the data before each sort.
            data_storage data_copy(data);

            pns.second(data_copy.begin(), data_copy.end(), cr);

            string file_out_name = "sorted_" + pns.first + "_" + cr.get_name() + ".csv";
            ofstream out_file(file_out_name);

            cout << "Writing to \"" << file_out_name << "\"..." << endl;

            write_row(headers.begin(), headers.end(), out_file);
            for (auto const& r : data_copy)
            {
                write_row(r.begin(), r.end(), out_file);
            }

            out_file.close();

            cout << endl;
        }
    }
}
