#pragma once

namespace Geometry
{
    template <typename T>
    inline constexpr T EPSILON = static_cast<T>(1e-9);

    template <>
    inline constexpr float EPSILON<float> = 1e-5f;

    template <>
    inline constexpr double EPSILON<double> = 1e-9;

    template <typename T>
    inline constexpr T EPSILON_SQR = EPSILON<T> * EPSILON<T>;
}