/*
 * random_data.h
 * Copyright (C) 2016  <@BLUEYI-PC>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef RANDOM_DATA_H
#define RANDOM_DATA_H
#include <vector>
#include <random>
#include <ctime>
#include <ostream>
#include <iostream>
#include <string>

std::vector<int> random_int(std::size_t count, int min = 0, int max = 100)
{
    std::vector<int> rint;
    std::default_random_engine e(time(NULL));
    std::uniform_int_distribution<int> u(min, max);
    for (std::size_t i = 0; i < count; ++i) {
        rint.push_back(u(e));
    }
    return rint;
}

std::vector<double> random_real(std::size_t count, int min = 0, int max = 100)
{
    std::vector<double> rreal;
    std::default_random_engine e(time(NULL));
    std::uniform_real_distribution<double> u(min, max);
    for (std::size_t i = 0; i < count; ++i) {
        rreal.push_back(u(e));
    }
    return rreal;
}

template <typename T> std::ostream& print(const std::vector<T> &vec, std::ostream &os = std::cout, const char ch = '0', const std::string &msg = "", T max = 100)
{
//    std::size_t i = 0;
//    while (i++ < vec.size())
//        os << i << "\t";
//    os << std::endl;
//
    if (!msg.empty())
        std::cout << "--- " << msg << " ---" << std::endl;
    for (auto v : vec)
      os << v << " ";
    os << std::endl;
    if (ch != '0') {
        for (auto v : vec) {
            os << std::string((std::size_t)((double)v / (double)max * 70.0) , ch) << " " << v << std::endl;
        }
    }
    os << std::endl;
    return os;
}

#endif /* !RANDOM_DATA_H */
