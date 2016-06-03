
#include<cmath>

#include "SRP.hpp"

template<class T>
SRP<T>::SRP() : DynamicSystem<T>(5) {


};
template<class T>
std::vector<T> SRP<T>::operator()(const double& time, const std::vector<T>& state) const{


    T mu = 170.0*3.14159/180.0; //Hard-coded, need to add Controller to DynamicSystem soon...
    double g = 3.71;
    double g0 = 9.81;
    double Isp = 295.0;
    double thrust = 4.8586e5;
    
    std::vector<T> dx;
    
    dx.resize(this->nStates);

    dx[0] = state[2];
    dx[1] = state[3];
    dx[2] = thrust/state[4]*cos(mu);
    dx[3] = -g + thrust/state[4]*sin(mu);
    dx[4] = -thrust/g0/Isp;
    
    return dx;



};


template class SRP<double>;
// template class SRP<DA>;