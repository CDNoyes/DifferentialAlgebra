#pragma once

#include<string>

#include <DA\dace.h>
using namespace DACE;

void printState(const std::vector<std::string>& state){

    int width = 15;
    std::cout << std::setw(width) << std::left << "t, s";
    for (auto& s : state)
        std::cout << std::setw(width) << std::left << s;
    std::cout << "\n";

}

void printState(const double& time, const std::vector<double>& state, const int& nDecimals = 6){

    int width = 15;
    std::cout << std::setprecision(nDecimals) << std::setw(width) << std::left << time;
    for (auto& s : state)
        std::cout << std::setw(width) << std::left << s;
    std::cout << "\n";
}


void printState(const double& time, const std::vector<DA>& state, const int& nDecimals = 6){

    int width = 15;
    std::cout << std::setprecision(nDecimals) << std::setw(width) << std::left << time;
    for (auto& s : state)
        std::cout << std::setw(width) << std::left << s.cons();
    std::cout << "\n";

};


void printState(const double& time, const std::vector<DA>& state, const std::vector<double> evalPoint, const int& nDecimals = 6){

    int width = 15;
    std::cout << std::setprecision(nDecimals) << std::setw(width) << std::left << time;
    for (auto& s : state)
        std::cout << std::setw(width) << std::left << s.eval(evalPoint);
    std::cout << "\n";

};

/* It might be overkill but a Printer class could keep track of the number of states, and notice if they change.
    It could also record the number of prints and print the header info every n prints*/