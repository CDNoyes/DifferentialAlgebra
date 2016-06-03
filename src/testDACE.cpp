#include <iostream>

#include "VectorOperations.hpp"
#include <DA\dace.h>

using namespace DACE;

int main()
{
    // std::cout << "Entered main(), checking DACE version compatability." << std::endl;
    
    // try { 
    // DA::checkVersion(); 
    // std::cout << "checkVersion() passed." << std::endl;
        // } 
    
    // catch(DACEException)
        // {
        // std::cout << "DACE Exception caught, version mismatch." <<std::endl;
        // }
    
    // int orderMax = DA::getMaxOrder();
    
    // std::cout << "Max order:" << orderMax << std::endl;

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

    
    return 0;
}