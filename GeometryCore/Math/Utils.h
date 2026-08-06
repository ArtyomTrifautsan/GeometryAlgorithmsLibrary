#pragma once

#include <cmath>
#include <algorithm>
#include <concepts>
#include <type_traits>

#include "GeometryCore/Math/Tolerance.h"
#include "GeometryCore/Math/Constants.h"


// === OLD AND WILL BE REMOVED ===
namespace Geometry
{
    // Custom abs that works in compile-time
    template <typename T>
    [[nodiscard]] constexpr T Abs(T value) noexcept
    {
        if (value == T(0)) return T(0); // need for -0.0 eauals to +0.0
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

    //template <std::floating_point T>
    //[[nodiscard]] constexpr bool AreEqual(T a, T b, T eps = EPSILON<T>) noexcept
    //{
    //    if (a == b) return true;
    //    T diff = Abs(a - b);
    //    if (diff <= eps) return true;
    //    return diff <= eps * std::max(Abs(a), Abs(b));
    //}

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





// === NEW ===

namespace Geometry
{
    //template <std::floating_point T>
    //[[nodiscard]] constexpr T Abs(T value) noexcept
    //{
    //    if (value == T(0)) return T(0);
    //    return value < T(0) ? -value : value;
    //}


    // Scalars

    template <std::floating_point T>
    [[nodiscard]] constexpr bool IsNumericallyZero(T value, const Tolerance<T>& tol = DefaultTolerance<T>) noexcept
    {
        return Abs(value) <= tol.mathEpsilon;
    }

    template <std::floating_point T>
    [[nodiscard]] constexpr bool AreNumericallyEqual(T a, T b, const Tolerance<T>& tol = DefaultTolerance<T>) noexcept
    {
        if (a == b) return true;

        T diff = Abs(a - b);
        if (diff <= tol.mathEpsilon) return true;

        return diff <= tol.mathEpsilon * std::max(Abs(a), Abs(b));
    }

    template <std::floating_point T>
    [[nodiscard]] constexpr bool IsNumericallyGreaterOrEqual(T a, T b, const Tolerance<T>& tol = DefaultTolerance<T>) noexcept
    {
        if (a >= b) return true;
        T diff = b - a;
        return diff <= tol.mathEpsilon * std::max(Abs(a), Abs(b));
    }

    template <std::floating_point T>
    [[nodiscard]] constexpr bool IsNumericallyLessOrEqual(T a, T b, const Tolerance<T>& tol = DefaultTolerance<T>) noexcept
    {
        if (a <= b) return true;
        T diff = a - b;
        return diff <= tol.mathEpsilon * std::max(Abs(a), Abs(b));
    }


    // Geometry

    template <std::floating_point T>
    [[nodiscard]] constexpr bool IsGeometricallyZero(T length, const Tolerance<T>& tol = DefaultTolerance<T>) noexcept
    {
        return Abs(length) <= tol.geometricTolerance;
    }

    template <std::floating_point T>
    [[nodiscard]] constexpr bool AreGeometricallyEqual(T l1, T l2, const Tolerance<T>& tol = DefaultTolerance<T>) noexcept
    {
        return Abs(l1 - l2) <= tol.geometricTolerance;
    }

    template <std::floating_point T>
    [[nodiscard]] constexpr bool IsGeometricallyGreaterOrEqual(T l1, T l2, const Tolerance<T>& tol = DefaultTolerance<T>) noexcept
    {
        return l1 >= (l2 - tol.geometricTolerance);
    }

    template <std::floating_point T>
    [[nodiscard]] constexpr bool IsGeometricallyLessOrEqual(T l1, T l2, const Tolerance<T>& tol = DefaultTolerance<T>) noexcept
    {
        return l1 <= (l2 + tol.geometricTolerance);
    }
}