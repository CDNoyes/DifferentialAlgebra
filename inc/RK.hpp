#pragma once

#include "VectorOperations.hpp"
#include "DynamicSystem.hpp"

/*
RK.hpp
Connor Noyes, 5/26/16

Defines Runge-Kutta classes used to numerically integrate dynamic systems.
Included integrators:
A classical 4th order
Prince Dormand 4(5) with adaptive stepsize


*/


class RK4 {
    
    public:
        static std::vector<double> step(const DynamicSystem<double>& sys, double& time, const std::vector<double>& state, const double& h);
        static std::vector<DA> step(const DynamicSystem<DA>& sys, double& time, const std::vector<DA>& state, const double& h);

};

class DOPRI45 {
    public:
        static std::vector<double> step(const DynamicSystem<double>& sys, double& time, const std::vector<double>& state, double& h, const double& tol = 1e-6, const double& hmin = 1e-5, const bool&  constStep = false);
        // static Integrate();
};

// class RKF45 {
    // public:
        // static std::vector<double> step(const DynamicSystem<double>& sys, const double& time, const std::vector<double>& state, double& h);
        
    // private:
        // const int s = 6;
        // const double[] c = {0.0, 0.25, 3.0/8.0, 12.0/13.0, 1.0, 0.5};

// }