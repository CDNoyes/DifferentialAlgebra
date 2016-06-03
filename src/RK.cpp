#include "RK.hpp"
#include<iostream> // debugging
#include<cmath> // min, max, pow

std::vector<double> RK4::step(const DynamicSystem<double>& sys, double& time, const std::vector<double>& state, const double& h) {

    std::vector<double> stateNew;
    stateNew.resize(sys.nStates);  // May be unnecessary, hard to tell. Could make this a method of sys i.e. sys.newState()
    
    std::vector<double> k1 = sys(time,       state);
    std::vector<double> k2 = sys(time+0.5*h, VectorSum(state, VectorScale(k1,0.5*h)));
    std::vector<double> k3 = sys(time+0.5*h, VectorSum(state, VectorScale(k2,0.5*h)));
    std::vector<double> k4 = sys(time+h,     VectorSum(state, VectorScale(k3,h)));

    stateNew = VectorSum(state,
               VectorScale( 
               VectorSum(
               VectorSum(k1,
               VectorScale(k2,2.0)),
               VectorSum(
               VectorScale(k3,2.0),k4) ), h/6.0)
               );
    time += h;
    return stateNew;
};

std::vector<DA> RK4::step(const DynamicSystem<DA>& sys, double& time, const std::vector<DA>& state, const double& h) {

    std::vector<DA> stateNew;
    stateNew.resize(sys.nStates);  
    
    std::vector<DA> k1 = sys(time,       state);
    std::vector<DA> k2 = sys(time+0.5*h, VectorSum(state, VectorScale(k1,0.5*h)));
    std::vector<DA> k3 = sys(time+0.5*h, VectorSum(state, VectorScale(k2,0.5*h)));
    std::vector<DA> k4 = sys(time+h,     VectorSum(state, VectorScale(k3,h)));
    
    
    stateNew = VectorSum(state,
               VectorScale( 
               VectorSum(
               VectorSum(k1,
               VectorScale(k2,2.0)),
               VectorSum(
               VectorScale(k3,2.0),k4) ), h/6.0)
               );
    time += h;
    return stateNew;
};






// This method could serve as a generic RK step method, with the number of stages and Butcher Tableau passed as inputs (or as a template argument).

std::vector<double> DOPRI45::step(const DynamicSystem<double>& sys, double& time, const std::vector<double>& state, double& h, const double& tol, const double& hmin, const bool& constStep) {

    // Butcher tableaus for:
   
   // Prince-Dormand 4/5
    const int s = 7;
    const int order = 5;
    const double c[s] = {0.0, 0.2, 0.3, 0.8, 8.0/9.0, 1.0, 1.0};
    const double a[s][s] = {{0},
                            {0.2},
                            {3.0/40.0, 9.0/40.0},
                            {44.0/45.0, -56.0/15.0, 32.0/9.0},
                            {19372.0/6561.0, -25360.0/2187.0, 64448.0/6561.0, -212.0/729.0},
                            {9017.0/3168.0, -355.0/33.0, 46732.0/5247.0, 49.0/176.0, -5103.0/18656.0},
                            {35.0/384.0, 0.0, 500.0/1113.0, 125.0/192.0, -2187.0/6784.0, 11.0/84.0} };
                            
    const double b5[s] = {35.0/384.0, 0.0, 500.0/1113.0, 125.0/192.0, -2187.0/6784.0, 11.0/84.0, 0.0};
    const double b4[s] = {5179.0/57600.0, 0.0, 7571.0/16695.0, 393.0/640.0, -92097.0/339200.0, 187.0/2100.0, 1.0/40.0};
    
    // Cash-Karp 4/5
    // const int s = 6;
    // const int order = 5;
    // const double c[s] = {0.0, 0.2, 0.3, 0.6, 1.0, 7.0/8.0};
    // const double a[s][s] = {{0},
                            // {0.2},
                            // {3.0/40.0, 9.0/40.0},
                            // {3.0/10.0, -9.0/10.0, 6.0/5.0},
                            // {-11.0/54.0, 5.0/2.0, -70.0/27.0, 35.0/27.0},
                            // {1631.0/55296.0,    175.0/512.0,    575.0/13824.0,    44275.0/110592.0,    253.0/4096.0}};
                            
    // const double b5[s] = {37.0/378.0, 0.0,    250.0/621.0,    125.0/5940.0,    0.0,    512.0/1771.0};
    // const double b4[s] = {2825.0/27648.0,    0.0,    18575.0/48384.0,    13525.0/55296.0,    277.0/14336.0,    1.0/4.0};
    
    // Runge-Kutta 4
    // const int s = 4;
    // const int order = 4;
    // const double c[s] = {0.0, 0.5, 0.5, 1.0};
    // const double a[s][s] = {{0},
                            // {0.5},
                            // {0.0, 0.5},
                            // {0.0, 0.0, 1.0}};
                            
    // const double b5[s] = {1.0/6.0, 1.0/3.0, 1.0/3.0, 1.0/6.0};
    // const double b4[s] = {0.0};
    

    // Stepsize Adaptation Algorithm parameters
    const int nStepsMax = 5;                    // Maximum number of steps to reject before giving up
    const double S = 0.9;                       // Stepsize safety factor
    const double minScale = 0.2;                // Minimum scale factor, never cut by more than 5x
    const double maxScale = 10.0;               // Maximum scale factor, never grow by more than 10x
    // const double beta = 0.0;                 // Integral gain (like a PI controller) for stepsize adaptation law, not implemented
    const double alpha = 1.0/order;// - beta*0.75;    // Proportional gain = 1/order
    double scale;
    
    // Initialize
    double errNorm = 0.0;
    std::vector<double> stateNew, err, temp;
    
    err.resize(sys.nStates, 0.0);
    stateNew.resize(sys.nStates, 0.0);  
    

    std::vector< std::vector<double> > k;
    k.resize(s, std::vector<double>(sys.nStates,0.0));
    
    k[0] = sys(time,state);
    
    for ( int nSteps = 0; nSteps < nStepsMax; nSteps++){
        
        stateNew = VectorSum(state, VectorScale(k[0],h*b5[0])); 
        err = VectorScale(k[0],h*(b5[0]-b4[0]));
        
        // The first k is computed above, so we start at i = 1
        for (int i = 1; i < s; i++){
            temp = state;                                                   // Reset each loop
            for (int j = 0; j < s; j++){
                if (a[i][j] != 0.0)                                         // Avoid expensive vector operations when we can
                    temp = VectorSum(temp, VectorScale(k[j],a[i][j]*h));
            }
            k[i] = sys(time+c[i]*h, temp);

            stateNew = VectorSum(stateNew, VectorScale(k[i],h*b5[i]) );     // 5th order candidate step
            err = VectorSum(err, VectorScale(k[i],h*(b5[i]-b4[i])));;       
        }    
        
        // Stepsize Adaptation
        // if (false) {
        if (!constStep) {
            errNorm = VectorNorm(err)/tol;                                      // norm could be replaced with max
            if (errNorm <= 1.0){
                if (errNorm == 0.0){
                    scale = maxScale;            
                }
                else {
                    if (nSteps == 0) {
                        scale = std::min(maxScale, std::max(minScale, S*std::pow(errNorm,-alpha) ) );}  // Previous step accepted so the step size can grow
                    else {
                        scale = std::min(1.0, std::max(minScale, S*std::pow(errNorm,-alpha) ) );}       // Previous step failed so maxScale is replaced by 1
                }
                
                time += h;
                h = std::max(hmin,h*scale);                 // Set the step size for next time            
                break;
            }
            else if (h == hmin) {           // If the error wasn't small enough but the stepsize is already as small as we allow, print a warning and move on
                // std::cout << "Warning: Unable to achieve specified error tolerance with minimum stepsize at t = " << time << " s.\n";
                time += h;
                break;
            } 
            else {
                if (nSteps == (nStepsMax-1)){
                    time += h;
                }
                h = std::max(h*std::max(S*std::pow(errNorm,-alpha),minScale), hmin); // Always update the step, whether for next attempt, or next call to Step
            }
        }
        else {
            time += h;
            break;
        }
        
    }

    return stateNew;
};