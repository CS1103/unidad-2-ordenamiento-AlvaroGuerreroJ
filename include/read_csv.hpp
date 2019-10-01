#ifndef GUARD_READ_CSV_HPP
#define GUARD_READ_CSV_HPP

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "lib/parser.hpp"

template<template<class...> class retcon = std::vector>
retcon<std::vector<std::string>> read_csv(std::string filename)
{
    std::ifstream f(filename);
    if (!f.is_open())
    {
        std::ostringstream os;
        os << "\"" << filename << "\"" << " can't be opened";
        throw std::domain_error(os.str());
    }
    aria::csv::CsvParser parser(f);

    retcon<std::vector<std::string>> ret(parser.begin(), parser.end());

    return ret;
}

#endif
