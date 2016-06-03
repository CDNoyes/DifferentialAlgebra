#pragma once

#include<algorithm> //std::transform
#include<vector>
#include<cmath>     //std::sqrt

#include <DA\dace.h>

using namespace DACE;

// Vectorized addition operations
inline std::vector<double> VectorSum(const std::vector<double>& v1, const std::vector<double>& v2){   
    std::vector<double> v3;
    v3.resize(v1.size());
    std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), [](const double& da, const double& d ){return da+d;});
    return v3;
}

inline std::vector<DA> VectorSum(const AlgebraicVector<DA>& v1, const std::vector<double>& v2){   
    AlgebraicVector<DA> v3;
    v3.resize(v1.size());
    std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), [](const DA& da, const double& d ){return da+d;}); 
    return v3;
}

inline std::vector<DA> VectorSum(const std::vector<double>& v1, const AlgebraicVector<DA>& v2){
    return VectorSum(v2, v1);
}

inline std::vector<DA> VectorSum(const AlgebraicVector<DA>& v1, const AlgebraicVector<DA>& v2){   
    AlgebraicVector<DA> v3;
    v3.resize(v1.size());
    std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), [](const DA& da, const DA& d ){return da+d;}); 
    return v3;
}


inline std::vector<double> VectorScale(const std::vector<double>& v1, const double s)
{   
    std::vector<double> vs;
    for (auto& i : v1 ) { vs.push_back(i*s); }
    return vs;
}

inline std::vector<DA> VectorScale(const std::vector<DA>& v1, const double s)
{   
    std::vector<DA> vs;
    for (auto& i : v1 ) { vs.push_back(i*s); }
    return vs;
}

inline double VectorNorm(const std::vector<double>& v1)
{
    double n = 0;
    for (auto& v : v1)
        n += v*v;
    
    
    return sqrt(n);
}