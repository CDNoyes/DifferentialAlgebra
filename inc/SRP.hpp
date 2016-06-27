#pragma once

#include "DynamicSystem.hpp"
// #include <DA\dace.h>

// using namespace DACE;


template<class T>
class SRP : public DynamicSystem<T> {

    // private:
        
    public:
        SRP();
        virtual std::vector<T> operator()(const double&, const std::vector<T>&, const std::function<T(const double&, const std::vector<T>&)>& control) const;     
};