#pragma once



template<class T>
constexpr const T& clamp(const T& v, const T& lo, const T& hi)
{

    if (v < lo)
        return lo;
    else if (v > hi)
        return hi;
    else
        return v;


}