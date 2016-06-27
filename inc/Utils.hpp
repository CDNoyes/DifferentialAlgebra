#pragma once
/*
Utils.hpp
Connor Noyes, 6/18/16

Defines the following MATLAB-like functions for numerical work:
    sign
    range
    linspace
    logspace

*/

#include<cmath>
#include<vector>
#include<iostream>
#include<stdexcept>

int sign(const double& val){

    double zeroTol = 1e-12;
    double posVal = std::abs(val);
    
    if (posVal < zeroTol) { return 0; }
    else { return (val >= zeroTol ? 1 : -1); }
    
};


std::vector<double> range(double a, const double& b, const double& step=1.0){
    
    std::vector<double> array;

    //Error checking here
    if (sign((b-a)/step)!=1){
        std::cout << "Improper step sign used in range.\n";
        throw std::invalid_argument("Improper step sign used in range.\n");   
    }
    

    if (sign(step) == 1){
        while(a <= b){
        
            array.push_back(a);
            a += step;
        
        }
    }
    else{
        while(a >= b){
            
                array.push_back(a);
                a += step;
            
            }
    }

    return array;
};

std::vector<double> linspace(double a, const double& b, const int& n=100) {

    if (n<2){
        std::cout << "Improper number of steps used in linspace.\n";
        throw std::invalid_argument("Improper number of steps used in linspace.\n");
    }
    
    std::vector<double> array;
    array.reserve(n);
    double epsilon = 0.0001;
    
    double step = (b-a) / (n-1);
    if (a==b)
    {
        for (int i = 0; i < n; i++)
        {
            array.push_back(a);
        }
    }
    else if (step >= 0)
    {
        while(a <= b + epsilon)
        {
            array.push_back(a);
            a += step;           
        }       
    }
    else
    {
        while(a + epsilon >= b )
        {
            array.push_back(a);
            a += step;           
        }       
    }
    return array;
};


std::vector<double> logspace(const double& pow1, const double& pow2, const int& n=50) {

    std::vector<double> linearPowers = linspace(pow1,pow2,n);
    
    std::vector<double> logPoints;
    logPoints.reserve(n);

    for (auto&& power : linearPowers)
        logPoints.push_back(pow(10.0,power));
    
    return logPoints;
};