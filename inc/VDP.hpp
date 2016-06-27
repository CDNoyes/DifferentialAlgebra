#pragma once

#include "DynamicSystem.hpp"
#include <DA\dace.h>

using namespace DACE;


class VDP : public DynamicSystem<double> {

    private:
        double MU;
        
    public:
        VDP(double mu);
        // virtual std::vector<double> operator()(const double&, const std::vector<double>&, const std::function<double(const double&, const std::vector<double>&)>& control) const;     
        virtual std::vector<double> operator()(const double&, const std::vector<double>&) const;     
};

class VDPDA : public DynamicSystem<DA> {

    private:
        DA MU;
        
    public:
        VDPDA(DA mu);
        // virtual std::vector<DA> operator()(const double&, const std::vector<DA>&, const std::function<DA(const double&, const std::vector<DA>&)>& control) const;     
        virtual std::vector<DA> operator()(const double&, const std::vector<DA>&) const;     
        inline DA mu() const {return this->MU;} ;
};