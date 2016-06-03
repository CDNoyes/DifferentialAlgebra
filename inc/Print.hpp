#pragma once

#include<string>

#include <DA\dace.h>
using namespace DACE;

int width = 15;

void printState(const std::vector<std::string>& state){
    
    std::cout << std::setw(width) << std::left << "t, s";
    for (auto& s : state)
        std::cout << std::setw(width) << std::left << s;
    std::cout << "\n";

}

void printState(const double& time, const std::vector<double>& state, const int& nDecimals = 6){

    // int width = 15;
    std::cout << std::setprecision(nDecimals) << std::setw(width) << std::left << time;
    for (auto& s : state)
        std::cout << std::setw(width) << std::left << s;
    std::cout << "\n";
}


void printState(const double& time, const std::vector<DA>& state, const int& nDecimals = 6){

    // int width = 15;
    std::cout << std::setprecision(nDecimals) << std::setw(width) << std::left << time;
    for (auto& s : state)
        std::cout << std::setw(width) << std::left << s.cons();
    std::cout << "\n";

};


void printState(const double& time, const std::vector<DA>& state, const std::vector<double> evalPoint, const int& nDecimals = 6){

    // int width = 15;
    std::cout << std::setprecision(nDecimals) << std::setw(width) << std::left << time;
    for (auto& s : state)
        std::cout << std::setw(width) << std::left << s.eval(evalPoint);
    std::cout << "\n";

};
