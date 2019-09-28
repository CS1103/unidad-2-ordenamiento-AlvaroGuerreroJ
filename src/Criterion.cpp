#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Criterion.hpp"

using std::map;
using std::ostringstream;
using std::string;
using std::vector;

Criterion::Criterion(string name, vector<string> const& headers,
                     vector<string> const& comparison_fields)
    : m_name(name)
{
    map<string, vector<string>::size_type> header_numbers;
    for (vector<string>::size_type i = 0; i < headers.size(); i++)
    {
        header_numbers[headers[i]] = i;
    }

    for (string const& cf : comparison_fields)
    {
        auto it = header_numbers.find(cf);
        if (it == header_numbers.end())
        {
            ostringstream os;
            os << cf << " is not the headers.";

            throw std::domain_error(os.str());
        }

        m_comparison_positions.push_back(it->second);
    }
}

bool Criterion::operator()(std::vector<std::string> l,
                           std::vector<std::string> r) const
{
    for (auto const& n : m_comparison_positions)
    {
        if (l[n] < r[n])
        {
            return true;
        }
        else if (l[n] > r[n])
        {
            return false;
        }
    }
    return false;
}

string Criterion::get_name() const
{
    return m_name;
}
