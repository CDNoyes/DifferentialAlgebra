#pragma once

/*
Controller.hpp
Connor Noyes, 5/26/16

Header-only implementation of several class templates for controllers, each derived from abstract base class Controller.

Included controller templates:
ConstControl:       A constant controller - not typically too useful, but works as a default for a null controller
InterpControl:      A linearly interpolating controller, useful for open loop controls
FeedbackControl:    A feedback controller

*/

#include<vector>
#include<cassert>

template<class T>
class Controller {

    protected:
        inline Controller(int m) : nControls(m) { };           // Base Constructor to set const nControls, only callable by derived classes

    public:
        int const nControls;
        // std::vector<T> previous;
        
        virtual ~Controller(){ };
        virtual T operator() (const T&) const = 0;
        virtual std::vector<T> operator()(const std::vector<T>&) const = 0;       // Pure virtual method makes this an abstract base class



};

template<class T>
class InterpControl : public Controller<T> {

    private:
        std::vector<T> x;
        std::vector<T> y;
        int n;
        
    public:
        
        inline InterpControl(const int& m, const std::vector<T>& x, const std::vector<T>& y) : x(x), y(y), n(x.size()), Controller<T>(m) { 
            assert(x.size() == y.size());            
        };
    
        inline virtual T operator() (const T& in) const {
        
            if (in < x[0])
                return x[0];
            else if (in >= x[n-1])
                return x[n-1];
            
            int i;
            for (i = 0; i < n; i++){
                if (x[i]==in)
                    return y[i];
                else if (x[i]>in)
                    return y[i-1] + (in-x[i-1])*(y[i]-y[i-1])/(x[i]-x[i-1]);            
            }
        };
        
        inline virtual std::vector<T> operator() (const std::vector<T>& inputs) const {
            std::vector<T> outputs;
            
            for (auto& in : inputs)
                outputs.push_back( operator()(in) );
            return outputs;        
        };

};

template<class T>
class ConstControl : public Controller<T> {

        private:
            const T value;
        public:

            inline ConstControl(const int& m, const T& val) : value(val), Controller<T>(m){ };
        
            inline T operator()() const {return value;}; // This is a special case, for other controllers an empty call is meaningless. Maybe it could return the previous control?
            inline virtual T operator() (const T&) const {return value;};
            inline virtual std::vector<T> operator() (const std::vector<T>& input) const { 
                std::vector<T> x(input.size(),value);
                return x; };
};

// template<class T>
// class LinearFeedbackControl : public Controller<T> {
    
    // private:
        // std::vector< <std::vector<T> > K; //gain
    
    // public:
        // inline LinearFeedbackControl(const int& m, 


// }