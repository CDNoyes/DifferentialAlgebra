
#include "Utils.hpp"
#include "VDP.hpp"
#include "RK.hpp"
#include "Print.hpp"

#include "spline.h"

#include <DA\dace.h>
using namespace DACE;



/* void TestSRP(){

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

}; */

void TestDoubleVDP(const std::vector<double>& dx){
    std::cout << "RK Vanderpol Integration:\n";
    VDP vdp(1.0+dx[2]);

    double tf = 12;
           
    double t = 0.0;
    std::vector<double> x = {3.0+dx[0],5.0+dx[1]};      

    // VDP vdp(1.0+dx[2]);
        
    printState({"x1","x2"});
    printState(t,x);
    double h = .1;
    while (t < tf) {
    
        if (t + h >= tf){
            x = RK4::step(vdp, t, x, tf-t);
            printState(t,x);       // Print final state

            break;}
        else
            x = DOPRI45::step(vdp, t, x, h);
        
        printState(t,x); //Print all integration steps
    }
    return;
}

compiledDA TestDAVDP(const int& order=2, const std::vector<double>& dx={0.0,0.0,0.0}){
    DA::init(order,2);
    
    
    DA mu = DA(1)+0.5;
    DA x1 = DA(3.0);
    DA x2 = DA(5.0);
    VDPDA vdp(mu);
    

    
    AlgebraicVector<DA> x;
    x.push_back(x1);
    x.push_back(x2);
    
    std::cout << vdp.mu() << "\n";
    std::cout << vdp.trace(x,x) << "\n";
    
    std::cout << "\nComputing order " << DA::getMaxOrder() << " DA representation of VDP:\n";
    double t = 0.0;
    double h = 0.01;
    // printState({"x1","x2"});
    // printState(t, x);
    
    for (auto idx = 0; idx < 500; ++idx) {
        x = RK4::step(vdp, t, x, h);
    }
    
    
    std::vector<double> rad;
    compiledDA xc = x.compile();

    // printState({"r_x1","r_x2"});
    for (auto& da : x)
        rad.push_back(da.convRadius(1e-3,2));
    // printState(t, rad);
    // printState(t,xc.eval(dx));
    // printState({"x1(dx)","x2(dx)"});
    // printState(t, x, dx);

    return xc;
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


void TestLambdaControl(){

    auto u = [](const double& t){ return -9/(1+t);};
    
    std::cout << u(2) << " == -3\n";

}

int main()
{
    std::ofstream outputFile;
    outputFile.open("res/temp.txt");
    outputFile.close();
    
    // std::cout << "\n~~~Vanderpol Oscillator test program~~~\n";
    // std::vector<double> dx = {0.0,0.0,0.0};
    std::vector<double> dx = {0.0};
    // TestDoubleVDP(dx);
    compiledDA xf = TestDAVDP(4,dx);
    
    // std::vector<double> mus = logspace(-2,0,100);
    std::vector<double> mus = linspace(0.29,0.71,50);
    // printState({"mu"},{"x1","x2"});
    for (auto&& mu : mus){
        dx[0] = mu-0.5;
        // printState(mu, xf.eval(dx));
        writeState(mu, xf.eval(dx));
    }
    // TestSpline();
    // TestTableau();
    // TestRef();
    // TestNorm();
    // TestController(dx);
    // TestSRP();
    // TestLambdaControl();
    return 0;
}















