#pragma once

#include<string>
#include<iomanip>
#include<iostream>
#include<fstream>

#include <DA\dace.h>
using namespace DACE;

int width = 15;

void printState(const std::vector<std::string>& state){
    // Prints header including time, and states in state vector
    std::cout << std::setw(width) << std::left << "t, s";
    for (auto& s : state)
        std::cout << std::setw(width) << std::left << s;
    std::cout << "\n";

}

void printState(const std::string& iv, const std::vector<std::string>& state){
    // Prints header with independent variable text in iv and state text in state
    std::cout << std::setw(width) << std::left << iv;
    for (auto& s : state)
        std::cout << std::setw(width) << std::left << s;
    std::cout << "\n";

}

void printState(const double& time, const std::vector<double>& state, const int& nDecimals = 6){

    std::cout << std::setprecision(nDecimals) << std::setw(width) << std::left << time;
    for (auto& s : state)
        std::cout << std::setw(width) << std::left << s;
    std::cout << "\n";
}


void printState(const double& time, const std::vector<DA>& state, const int& nDecimals = 6){

    std::cout << std::setprecision(nDecimals) << std::setw(width) << std::left << time;
    for (auto& s : state)
        std::cout << std::setw(width) << std::left << s.cons();
    std::cout << "\n";

};


void printState(const double& time, const std::vector<DA>& state, const std::vector<double> evalPoint, const int& nDecimals = 6){

    std::cout << std::setprecision(nDecimals) << std::setw(width) << std::left << time;
    for (auto& s : state)
        std::cout << std::setw(width) << std::left << s.eval(evalPoint);
    std::cout << "\n";

};



void writeState(const double& time, const std::vector<double>& state, const int& nDecimals = 6){
    
    std::ofstream outputFile;
    
    outputFile.open("res/temp.txt", std::fstream::out | std::fstream::app);
    
    outputFile << std::setprecision(nDecimals) << std::setw(width) << std::left << time;
    for (auto& s : state)
        outputFile << std::setw(width) << std::left << s;
    outputFile << "\n";
    outputFile.close();
}

// void writeState(const double& time, const std::vector<double>& state, const std::vector<std::string>& filename, const int& nDecimals = 6){
    
    // std::ofstream outputFile;
    
    // outputFile.open("res/" + filename);
    
    // outputFile << std::setprecision(nDecimals) << std::setw(width) << std::left << time;
    // for (auto& s : state)
        // outputFile << std::setw(width) << std::left << s;
    // outputFile << "\n";
// }