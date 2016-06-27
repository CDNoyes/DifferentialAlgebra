#pragma once
#include<vector>
#include<functional> //std::function


// #include "Controller.hpp"

/*
DynamicSystem.hpp
Connor Noyes, 5/24/16

Defines an abstract base class template for dynamic systems.
Derived systems must:
1) implement the pure virtual method operator() to return the system's dynamics
2) pass the appropriate value of nStates to this base class's constructor since it is declared const

*/

template<class T> 
class DynamicSystem {
    
    
    protected:
        inline DynamicSystem(int n) : nStates(n){ };                        // Base Constructor to set const nStates, only callable by derived classes

    public:
        int const nStates;                                                  // I want to be able to read this value, hence public. Const for safety.
        
        virtual ~DynamicSystem(){ };                                        // Virtual destructor to ensure derived destructors are called appropriately (prevents mem leaks)
        // virtual std::vector<T> operator()(
            // const double& time,
            // const std::vector<T>& state,
            // const std::function<T(const double&, const std::vector<T>&)>& control) const = 0;       // Pure virtual method makes this an abstract base class
        
        virtual std::vector<T> operator()(
            const double& time,
            const std::vector<T>& state) const = 0;       // Pure virtual method makes this an abstract base class
            
        virtual T trace(const std::vector<T>& state, const std::vector<T>& control) const { return T(0.0); };    
};

