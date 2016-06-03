#include<iostream>
#include<iomanip>

// #include "VectorOperations.hpp"
#include "VDP.hpp"
#include "RK.hpp"
#include "Controller.hpp"
#include "SRP.hpp"
#include "Print.hpp"
#include "spline.h"
// #include "DA\dace.h"
// using namespace DACE;



void TestSRP(){

    SRP<double> srp = SRP<double>();
    double tf = 18.1;
    double t = 0.0;
    std::vector<double> x = {0.0, 1000.0, 500.0, -150.0, 8500.0};        
           
    
    // std::vector<std::string> states = {"x", "y", "u", "v", "m"};
    printState({"x, m", "y, m", "u, m/s", "v, m/s", "mass, kg"});
    // printState(states);
    printState(t,x);
    double h = .1;
    while (t < tf) {
    
        if (t + h >= tf){
            x = RK4::step(srp, t, x, tf-t);
            break;}
        else
            x = DOPRI45::step(srp, t, x, h);
        
    printState(t,x);

    }
    printState(t,x);

};

void TestDoubleVDP(const std::vector<double>& dx){
    std::cout << "RK Vanderpol Integration:\n";
    {
        VDP vdp(1.0);
        double tf = 12;
               
        {
        double t = 0.0;
        std::vector<double> x = {3.0+dx[0],5.0+dx[1]};        
                
        std::cout << "\nT         x1         x2" << std::endl;
        std::cout << t << "        " << x[0] << "       " << x[1] << std::endl;
        double h = .1;
        while (t < tf) {
        
            if (t + h >= tf){
                x = RK4::step(vdp, t, x, tf-t);
                break;}
            else
                x = DOPRI45::step(vdp, t, x, h);
            
            std::cout << t << "       " << x[0] << "       " << x[1] << "\n"; //Print all integration steps
        }
        std::cout << t << "       " << x[0] << "       " << x[1] << "\n";       // Print final state

        }
    }

    return;
}

void TestDAVDP(const std::vector<double>& dx){
    DA::init(2,2);
    DA mu = DA(1.0);
    DA x1 = 3+DA(1);
    DA x2 = 5+DA(2);

    VDPDA vdp(mu);
    
    std::vector<DA> x;
    x.push_back(x1);
    x.push_back(x2);
    std::cout << "\nDA representation of VDP:\n";
    double t = 0.0;
    double h = 0.01;
    for (auto idx = 0; idx < 1200; ++idx) {
        x = RK4::step(vdp, t, x, h);
        // std::cout << t << "\n" << x[0] << "\n" << x[1] << "\n";
    }
    printState({"x1","x2"});
    printState(t, x);
    printState({"x1(dx)","x2(dx)"});
    printState(t, x, dx);
    // std::cout << t << "       " << x[0].eval(dx) << "       " << x[1].eval(dx) << "\n";
    // std::cout << t << "       " << x[0].cons() << "       " << x[1].cons() << "\n";


    return;
}

void TestSpline(){

    std::vector<double> x = {0,1,2,3,3.4,3.6,4};
    std::vector<double> y;
    
    for (auto& i : x)
        y.push_back(i*i - 1.0);
        
    tk::spline interp;
    interp.set_points(x,y);
    
    std::cout << interp(3.5) << " approx. = 11.25\n";
    
    

}

void TestTableau(){
    const double a[][7] = { {0.0},
                            {0.2},
                            {3.0/40.0, 9.0/40.0},
                            {44.0/45.0, -56.0/15.0, 32.0/9.0},
                            {19372.0/6561.0, -25360.0/2187.0, 64448.0/6561.0, -212.0/729.0},
                            {9017.0/3168.0, -355.0/33.0, 46732.0/5247.0, 49.0/176.0, -5103.0/18656},
                            {35.0/384.0, 0.0, 500.0/1113.0, 125.0/192.0, -2187.0/6784.0, 11.0/84.0} };
                            
    for (int i = 0; i<7; i++){
        for (int j = 0; j<7; j++){
            std::cout << a[i][j] << ", ";}
        std::cout << "\n";    

    }    
    // std::cout << (a[1][1] == 0.0) << std::endl;
    
        std::vector< std::vector<double> > k;
    k.resize(2,std::vector<double>(1,0.0));

    std::vector<double> x = {1,2};

    k[0] = x;
    std::cout << k[0][1];
    
    return;
}
void refFun(double& d)
{
    d += 5.0;
    return;
}
void TestRef()
{   
    double p = 5;
    refFun(p);
    std::cout << p;

}

void TestNorm()
{

std::vector<double> x = {1,2,3,4,5};
std::cout << VectorNorm(x) << "\n";

}

void TestController(const std::vector<double>& x){
    ConstControl<double> u(1,3.0);

    std::cout << u() << std::endl; //Print out the previous control. For constControls, its the constant values. For all others, the value is intialized as 0
    
    std::vector<double> ux = u(x);
    std::cout << ux.size() << std::endl;
    
    std::vector<double> t = {0,1,2,3,4,5};
    std::vector<double> y = {0,1,4,9,16,25};
    
    InterpControl<double> ui(1,t,y);
    
    std::cout << ui(0.5) << "\n";
    std::cout << ui(t)[4] << "\n";
}

int main()
{
    std::cout << "\n~~~Vanderpol Oscillator test program~~~\n";
    std::vector<double> dx = {0.01, -0.03};
    TestDoubleVDP(dx);
    TestDAVDP(dx);
    // TestSpline();
    // TestTableau();
    // TestRef();
    // TestNorm();
    // TestController(dx);
    // TestSRP();
    return 0;
}















