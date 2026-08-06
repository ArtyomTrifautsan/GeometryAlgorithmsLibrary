#pragma once

#include <limits>
#include <concepts>

namespace Geometry
{
    template <std::floating_point T>
    struct Tolerance
    {
        T mathEpsilon;
        T geometricTolerance;
    };

    template <std::floating_point T>
    inline constexpr Tolerance<T> DefaultTolerance;

    template <>
    inline constexpr Tolerance<float> DefaultTolerance<float> = {
        std::numeric_limits<float>::epsilon(),
        1e-5f
    };

    template <>
    inline constexpr Tolerance<double> DefaultTolerance<double> = {
        std::numeric_limits<double>::epsilon(),
        1e-9
    };
}