#ifndef GUARD_READ_CSV_HPP
#define GUARD_READ_CSV_HPP

#include <fstream>
#include <string>
#include <vector>

#include "lib/parser.hpp"

template<template<class...> class retcon = std::vector>
retcon<std::vector<std::string>> read_csv(std::string filename)
{
    std::ifstream f(filename);
    aria::csv::CsvParser parser(f);

    retcon<std::vector<std::string>> ret(parser.begin(), parser.end());

    return ret;
}

#endif
