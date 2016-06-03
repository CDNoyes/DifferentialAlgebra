#pragma once

#include "DynamicSystem.hpp"
#include <DA\dace.h>

using namespace DACE;


class VDP : public DynamicSystem<double> {

    private:
        double MU;
        
    public:
        VDP(double mu);
        // using DynamicSystem::operator();
        virtual std::vector<double> operator()(const double&, const std::vector<double>&) const;     
};

class VDPDA : public DynamicSystem<DA> {

    private:
        DA MU;
        
    public:
        VDPDA(DA mu);
        // using DynamicSystem::operator();
        virtual std::vector<DA> operator()(const double&, const std::vector<DA>&) const;     

};