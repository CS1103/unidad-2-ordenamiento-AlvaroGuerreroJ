#ifndef GUARD_CRITERION_HPP
#define GUARD_CRITERION_HPP

#include <string>
#include <vector>

class Criterion
{
private:
    std::string m_name;
    std::vector<std::vector<std::string>::size_type> m_comparison_positions;

public:
    Criterion(std::string name, std::vector<std::string> const& headers,
              std::vector<std::string> const& criterions);
    ~Criterion() = default;

    bool operator()(std::vector<std::string> l, std::vector<std::string> r) const;

    std::string get_name() const;
};

#endif
