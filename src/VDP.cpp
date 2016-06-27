#include<iostream>

#include "VDP.hpp"

using namespace DACE;


VDP::VDP(double mu) : DynamicSystem<double>(2) {
    MU = mu;
};


// std::vector<double> VDP::operator()(const double& time, const std::vector<double>& state, const std::function<double(const double&, const std::vector<double>&)>& control) const {
std::vector<double> VDP::operator()(const double& time, const std::vector<double>& state) const {

    std::vector<double> dx;
    
    dx.resize(nStates);

    dx[0] = state[1];
    // dx[1] = (-state[0] + MU*(1-state[0]*state[0])*state[1]) + control(time, state);
    dx[1] = (-state[0] + MU*(1-state[0]*state[0])*state[1]);

    return dx;
}

VDPDA::VDPDA(DA mu) : DynamicSystem<DA>(2) {
    if (!DA::isInitialized()){std::cout<<"Warning: VDPDA class constructor called but DA has not been initialized!\n";};
    MU = mu;
};

// std::vector<DA> VDPDA::operator()(const double& time, const std::vector<DA>& state, const std::function<DA(const double&, const std::vector<DA>&)>& control) const {
    // std::vector<DA> dx;
    
    // dx.resize(nStates);

    // dx[0] = state[1];
    // dx[1] = (-state[0] + MU*(1-state[0]*state[0])*state[1]);

    // return dx;
// }

std::vector<DA> VDPDA::operator()(const double& time, const std::vector<DA>& state) const {
    std::vector<DA> dx;
    
    dx.resize(nStates);

    dx[0] = state[1];
    dx[1] = (-state[0] + MU*(1-state[0]*state[0])*state[1]);

    return dx;
}