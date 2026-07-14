#pragma once

#include <cmath>
#include <limits>

#include "Constants.h"

namespace Geometry
{
    // Custom abs that works in compile-time
    template <typename T>
    [[nodiscard]] constexpr T Abs(T value) noexcept
    {
        return value < T(0) ? -value : value;
    }

    template <typename T>
    [[nodiscard]] constexpr bool IsZero(T value) noexcept
    {
        return Abs(value) <= EPSILON<T>;
    }

    template <typename T>
    [[nodiscard]] constexpr bool IsZero(T value, T EPS) noexcept
    {
        return Abs(value) <= EPS;
    }

    template <typename T>
    [[nodiscard]] constexpr bool AreEqual(T a, T b) noexcept
    {
        return Abs(a - b) <= EPSILON<T>;
    }

    template <typename T>
    [[nodiscard]] constexpr bool IsGreaterOrEqual(T a, T b) noexcept
    {
        return a >= (b - EPSILON<T>);
    }

    template <typename T>
    [[nodiscard]] constexpr bool IsGreaterOrEqual(T a, T b, T EPS) noexcept
    {
        return a >= (b - EPS);
    }

    template <typename T>
    [[nodiscard]] constexpr bool IsLessOrEqual(T a, T b) noexcept
    {
        return a <= (b + EPSILON<T>);
    }

    template <typename T>
    [[nodiscard]] constexpr bool IsLessOrEqual(T a, T b, T EPS) noexcept
    {
        return a <= (b + EPS);
    }
}