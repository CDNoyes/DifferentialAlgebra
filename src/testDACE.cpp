#include <iostream>
#include<functional> //std::function

#include "Utils.hpp"
#include "VectorOperations.hpp"
#include <DA\dace.h>

using namespace DACE;


double myFun(const double t, const double state){ return -state/(1.0+t);}; // So I can write my control laws like this

template<class fun>
double testFun(const fun& control, const double t, const double state=0){ // and template all classes from now on..........

    return control(t, state); // and the call to control won't be generic, if additional data is needed, it will have to be passed explicitly

};


void testUtils(){

    std::cout << "Sign of -1.1 is " << sign(-1.1) << "\n";
    std::cout << "Sign of 0 is " << sign(0.0) << "\n";
    std::cout << "Sign of 1 is " << sign(1.0) << "\n";
    
    std::vector<double> x,y,z;
    
    x = linspace(0,1,7);
    y = range(1.0,10.0,1.1);
    z = logspace(-2,0,25);
    for (auto& e : x)
        std::cout << e << "\n";
        
    for (auto& e : y)
        std::cout << e << "\n";    
    for (auto& e : z)
        std::cout << e << "\n"; 
};

int main()
{
	DA::init(20, 2);
    
    std::cout << "Initialized the DA order: " << DA::getMaxOrder() << std::endl;

	DA x = DA(1);
    DA y = DA(2);
    std::cout << "Initialized a DA variables x,y:" << std::endl << x << std::endl << y << std::endl;
      
    AlgebraicVector<DA> state;  
    state.push_back(x);
    state.push_back(y);
    state = VectorSum(state,state);
    
    
    
    std::cout << "Set state :" << std::endl << state[0] << std::endl;
    
    // DA y1 = (y+x.sin()).deriv(2);
    
	// std::cout << "Set y1 = d/dy(y+sin(x)):" << std::endl << y1 << std::endl;
    
    // std::cout << "y1(3.14):" << std::endl << y1.evalScalar(3.14) << std::endl;

    std::cout << testFun(myFun,1.0, 5.0) << "\n"; 
    
    testUtils();
    
    return 0;
}