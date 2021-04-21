#pragma once
#ifndef INCLUDED_GYSANG_CMATH
// \cond macro-verbose-255
#define INCLUDED_GYSANG_CMATH

#include <gympl/platform.hpp>

#include <gysang/gysang.hpp>

// \endcond

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#include <cmath>
#include <math.h>

#if _MSC_VER <= 1900
#pragma warning(push)
#pragma warning(disable : 4814) // MS
#endif

namespace gysang
{
    template<typename V, AngleType Base>
    inline constexpr Angle<V, Base> abs(Angle<V, Base> const& v) noexcept(noexcept(Angle<V, Base>(std::abs(v.value()))))
    {
        return Angle<V, Base>(std::abs(v.value()));
    }
#ifdef GYMPL_HAS_CPP14
    template<typename V, AngleType Base>
    inline constexpr Angle<V, Base> abs(Angle<V, Base>&& v) noexcept(noexcept(v.value() = std::abs(v.value())))
    {
        v.value() = std::abs(v.value());
        return v;
    }
#endif

    template<typename V, AngleType Base>
    inline constexpr Angle<V, Base> fabs(Angle<V, Base> const& v) noexcept(noexcept(abs(v)))
    {
        return abs(v);
    }
#ifdef GYMPL_HAS_CPP14
    template<typename V, AngleType Base>
    inline constexpr Angle<V, Base> fabs(Angle<V, Base>&& v) noexcept(noexcept(abs(std::forward<Angle<V, Base>>(v))))
    {
        return abs(std::forward<Angle<V, Base>>(v));
    }
#endif

    template<typename Vleft, typename Vright, AngleType BaseLeft>
    constexpr Angle<typename angleTraits::BiggestResolution<Vleft, Vright>::type, BaseLeft> fmod(
        Angle<Vleft, BaseLeft> const& left,
        Vright right) noexcept(noexcept(Angle<typename angleTraits::BiggestResolution<Vleft, Vright>::type,
                                              BaseLeft>(std::fmod(left.value(), right))))
    {
        return Angle<typename angleTraits::BiggestResolution<Vleft, Vright>::type, BaseLeft>(std::fmod(left.value(), right));
    }

    template<typename Vleft, typename Vright, AngleType BaseLeft>
    constexpr Angle<typename angleTraits::BiggestResolution<Vleft, Vright>::type, BaseLeft> remainder(
        Angle<Vleft, BaseLeft> const& left,
        Vright right) noexcept(noexcept(Angle<typename angleTraits::BiggestResolution<Vleft, Vright>::type,
                                              BaseLeft>(std::remainder(left.value(), right))))
    {
        return Angle<typename angleTraits::BiggestResolution<Vleft, Vright>::type, BaseLeft>(std::remainder(left.value(), right));
    }

    template<typename Vleft, typename Vright, AngleType BaseLeft>
    constexpr Angle<typename angleTraits::BiggestResolution<Vleft, Vright>::type, BaseLeft> remquo(
        Angle<Vleft, BaseLeft> const& left, Vright right,
        int* quo) noexcept(noexcept(Angle<typename angleTraits::BiggestResolution<Vleft, Vright>::type,
                                          BaseLeft>(std::remquo(left.value(), right, quo))))
    {
        return Angle<typename angleTraits::BiggestResolution<Vleft, Vright>::type, BaseLeft>(std::remquo(left.value(), right, quo));
    }

    template<typename Vx, typename Vy, typename Vz, AngleType BaseX, AngleType BaseZ>
    constexpr Angle<typename angleTraits::BiggestResolution<Vx, Vy, Vz>::type, BaseX> fma(
        Angle<Vx, BaseX> const& x, Vy y,
        Angle<Vz, BaseZ> const& z) noexcept(noexcept(Angle<typename angleTraits::BiggestResolution<Vx, Vy, Vz>::type,
                                                           BaseX>(std::fma(x.value(), y, z.template valueAs<Vx, BaseX>()))))
    {
        return Angle<typename angleTraits::BiggestResolution<Vx, Vy, Vz>::type, BaseX>(
            std::fma(x.value(), y, z.template valueAs<Vx, BaseX>()));
    }

    template<typename Vleft, typename Vright, AngleType BaseLeft, AngleType BaseRight>
    constexpr Angle<typename angleTraits::BiggestResolution<Vleft, Vright>::type, BaseLeft> fmax(
        Angle<Vleft, BaseLeft> const& left,
        Angle<Vright, BaseRight> const& right) noexcept(noexcept(Angle<typename angleTraits::BiggestResolution<Vleft, Vright>::type,
                                                                       BaseLeft>(std::fmax(left.value(),
                                                                                           right.template valueAs<BaseLeft>()))))
    {
        return Angle<typename angleTraits::BiggestResolution<Vleft, Vright>::type, BaseLeft>(
            std::fmax(left.value(), right.template valueAs<BaseLeft>()));
    }
    template<typename Vleft, typename Vright, AngleType BaseLeft, AngleType BaseRight>
    constexpr Angle<typename angleTraits::BiggestResolution<Vleft, Vright>::type, BaseLeft> max(
        Angle<Vleft, BaseLeft> const& left, Angle<Vright, BaseRight> const& right) noexcept(noexcept(fmax(left, right)))
    {
        return fmax(left, right);
    }

    template<typename Vleft, typename Vright, AngleType BaseLeft, AngleType BaseRight>
    constexpr Angle<typename angleTraits::BiggestResolution<Vleft, Vright>::type, BaseLeft> fmin(
        Angle<Vleft, BaseLeft> const& left,
        Angle<Vright, BaseRight> const& right) noexcept(noexcept(Angle<typename angleTraits::BiggestResolution<Vleft, Vright>::type,
                                                                       BaseLeft>(std::fmin(left.value(),
                                                                                           right.template valueAs<BaseLeft>()))))
    {
        return Angle<typename angleTraits::BiggestResolution<Vleft, Vright>::type, BaseLeft>(
            std::fmin(left.value(), right.template valueAs<BaseLeft>()));
    }
    template<typename Vleft, typename Vright, AngleType BaseLeft, AngleType BaseRight>
    constexpr Angle<typename angleTraits::BiggestResolution<Vleft, Vright>::type, BaseLeft> min(
        Angle<Vleft, BaseLeft> const& left, Angle<Vright, BaseRight> const& right) noexcept(noexcept(left, right))
    {
        return fmin(left, right);
    }

    template<typename Vleft, typename Vright, AngleType BaseLeft, AngleType BaseRight>
    constexpr Angle<typename angleTraits::BiggestResolution<Vleft, Vright>::type, BaseLeft> fdim(
        Angle<Vleft, BaseLeft> const& left,
        Angle<Vright, BaseRight> const& right) noexcept(noexcept(Angle<typename angleTraits::BiggestResolution<Vleft, Vright>::type,
                                                                       BaseLeft>(std::fdim(left.value(),
                                                                                           right.template valueAs<BaseLeft>()))))
    {
        return Angle<typename angleTraits::BiggestResolution<Vleft, Vright>::type, BaseLeft>(
            std::fdim(left.value(), right.template valueAs<BaseLeft>()));
    }

#if defined(GYMPL_HAS_LERP)
    template<typename Vleft, typename Vright, AngleType BaseLeft, AngleType BaseRight, typename Vt>
    constexpr Angle<typename angleTraits::BiggestResolution<Vleft, Vright>::type, BaseLeft> lerp(
        Angle<Vleft, BaseLeft> const& left, Angle<Vright, BaseRight> const& right,
        Vt t) noexcept(noexcept(Angle<typename angleTraits::BiggestResolution<Vleft, Vright>::type,
                                      BaseLeft>(std::lerp(left.value(), right.template valueAs<BaseLeft>(), t))))
    {
        return Angle<typename angleTraits::BiggestResolution<Vleft, Vright>::type, BaseLeft>(
            std::lerp(left.value(), right.template valueAs<BaseLeft>(), t));
    }
#endif

    template<typename V>
    inline constexpr V sin(Angle<V, AngleType::AngleType_Radian> const& v) noexcept(noexcept(std::sin(v.value())))
    {
        return std::sin(v.value());
    }
    template<typename V>
    inline constexpr V sin(Angle<V, AngleType::AngleType_Radian>&& v) noexcept(noexcept(std::sin(v.value())))
    {
        return std::sin(v.value());
    }
    template<typename V>
    inline constexpr V sin(Angle<V, AngleType::AngleType_Degree> const& v) noexcept(
        noexcept(std::sin(v.template valueAs<AngleType::AngleType_Radian>())))
    {
        return std::sin(v.template valueAs<AngleType::AngleType_Radian>());
    }
    template<typename V>
    inline constexpr V sin(Angle<V, AngleType::AngleType_Degree>&& v) noexcept(
        noexcept(std::sin(v.template valueAs<AngleType::AngleType_Radian>())))
    {
        return std::sin(v.template valueAs<AngleType::AngleType_Radian>());
    }

    template<typename V>
    inline constexpr V cos(Angle<V, AngleType::AngleType_Radian> const& v) noexcept(noexcept(std::cos(v.value())))
    {
        return std::cos(v.value());
    }
    template<typename V>
    inline constexpr V cos(Angle<V, AngleType::AngleType_Radian>&& v) noexcept(noexcept(std::cos(v.value())))
    {
        return std::cos(v.value());
    }
    template<typename V>
    inline constexpr V cos(Angle<V, AngleType::AngleType_Degree> const& v) noexcept(
        noexcept(std::cos(v.template valueAs<AngleType::AngleType_Radian>())))
    {
        return std::cos(v.template valueAs<AngleType::AngleType_Radian>());
    }
    template<typename V>
    inline constexpr V cos(Angle<V, AngleType::AngleType_Degree>&& v) noexcept(
        noexcept(std::cos(v.template valueAs<AngleType::AngleType_Radian>())))
    {
        return std::cos(v.template valueAs<AngleType::AngleType_Radian>());
    }

    template<typename V>
    inline constexpr V tan(Angle<V, AngleType::AngleType_Radian> const& v) noexcept(noexcept(std::tan(v.value())))
    {
        return std::tan(v.value());
    }
    template<typename V>
    inline constexpr V tan(Angle<V, AngleType::AngleType_Radian>&& v) noexcept(noexcept(std::tan(v.value())))
    {
        return std::tan(v.value());
    }
    template<typename V>
    inline constexpr V tan(Angle<V, AngleType::AngleType_Degree> const& v) noexcept(
        noexcept(std::tan(v.template valueAs<AngleType::AngleType_Radian>())))
    {
        return std::tan(v.template valueAs<AngleType::AngleType_Radian>());
    }
    template<typename V>
    inline constexpr V tan(Angle<V, AngleType::AngleType_Degree>&& v) noexcept(
        noexcept(std::tan(v.template valueAs<AngleType::AngleType_Radian>())))
    {
        return std::tan(v.template valueAs<AngleType::AngleType_Radian>());
    }

    template<typename V, AngleType Base>
    inline constexpr Angle<V, Base> ceil(Angle<V, Base> const& v) noexcept(noexcept(Angle<V, Base>(std::ceil(v.value()))))
    {
        return Angle<V, Base>(std::ceil(v.value()));
    }
#ifdef GYMPL_HAS_CPP14
    template<typename V, AngleType Base>
    inline constexpr Angle<V, Base> ceil(Angle<V, Base>&& v) noexcept(noexcept(v.value() = std::ceil(v.value())))
    {
        v.value() = std::ceil(v.value());
        return v;
    }
#endif

    template<typename V, AngleType Base>
    inline constexpr Angle<V, Base> floor(Angle<V, Base> const& v) noexcept(noexcept(Angle<V, Base>(std::floor(v.value()))))
    {
        return Angle<V, Base>(std::floor(v.value()));
    }
#ifdef GYMPL_HAS_CPP14
    template<typename V, AngleType Base>
    inline constexpr Angle<V, Base> floor(Angle<V, Base>&& v) noexcept(noexcept(v.value() = std::floor(v.value())))
    {
        v.value() = std::floor(v.value());
        return v;
    }
#endif

    template<typename V, AngleType Base>
    inline constexpr Angle<V, Base> trunc(Angle<V, Base> const& v) noexcept(noexcept(Angle<V, Base>(std::trunc(v.value()))))
    {
        return Angle<V, Base>(std::trunc(v.value()));
    }
#ifdef GYMPL_HAS_CPP14
    template<typename V, AngleType Base>
    inline constexpr Angle<V, Base> trunc(Angle<V, Base>&& v) noexcept(noexcept(v.value() = std::trunc(v.value())))
    {
        v.value() = std::trunc(v.value());
        return v;
    }
#endif

    template<typename V, AngleType Base>
    inline constexpr Angle<V, Base> round(Angle<V, Base> const& v) noexcept(noexcept(Angle<V, Base>(std::round(v.value()))))
    {
        return Angle<V, Base>(std::round(v.value()));
    }
#ifdef GYMPL_HAS_CPP14
    template<typename V, AngleType Base>
    inline constexpr Angle<V, Base> round(Angle<V, Base>&& v) noexcept(noexcept(v.value() = std::round(v.value())))
    {
        v.value() = std::round(v.value());
        return v;
    }
#endif

    template<typename V, AngleType Base>
    inline constexpr Angle<V, Base> nearbyint(Angle<V, Base> const& v) noexcept(noexcept(Angle<V, Base>(std::nearbyint(v.value()))))
    {
        return Angle<V, Base>(std::nearbyint(v.value()));
    }
#ifdef GYMPL_HAS_CPP14
    template<typename V, AngleType Base>
    inline constexpr Angle<V, Base> nearbyint(Angle<V, Base>&& v) noexcept(noexcept(v.value() = std::nearbyint(v.value())))
    {
        v.value() = std::nearbyint(v.value());
        return v;
    }
#endif

    template<typename V, AngleType Base>
    inline constexpr Angle<V, Base> rint(Angle<V, Base> const& v) noexcept(noexcept(Angle<V, Base>(std::rint(v.value()))))
    {
        return Angle<V, Base>(std::rint(v.value()));
    }
#ifdef GYMPL_HAS_CPP14
    template<typename V, AngleType Base>
    inline constexpr Angle<V, Base> rint(Angle<V, Base>&& v) noexcept(noexcept(v.value() = std::rint(v.value())))
    {
        v.value() = std::rint(v.value());
        return v;
    }
#endif

    template<typename V, AngleType Base>
    inline constexpr int fpclassify(Angle<V, Base> const& v) noexcept(noexcept(std::fpclassify(v.value())))
    {
        return std::fpclassify(v.value());
    }
    template<typename V, AngleType Base>
    inline constexpr bool isfinite(Angle<V, Base> const& v) noexcept(noexcept(std::isfinite(v.value())))
    {
        return std::isfinite(v.value());
    }
    template<typename V, AngleType Base>
    inline constexpr bool isinf(Angle<V, Base> const& v) noexcept(noexcept(std::isinf(v.value())))
    {
        return std::isinf(v.value());
    }
    template<typename V, AngleType Base>
    inline constexpr bool isnan(Angle<V, Base> const& v) noexcept(noexcept(std::isnan(v.value())))
    {
        return std::isnan(v.value());
    }
    template<typename V, AngleType Base>
    inline constexpr bool isnormal(Angle<V, Base> const& v) noexcept(noexcept(std::isnormal(v.value())))
    {
        return std::isnormal(v.value());
    }
    template<typename V, AngleType Base>
    inline constexpr bool signbit(Angle<V, Base> const& v) noexcept(noexcept(std::signbit(v.value())))
    {
        return std::signbit(v.value());
    }
    template<typename V, AngleType Base>
    inline constexpr bool isgreater(Angle<V, Base> const& v1,
                                    Angle<V, Base> const& v2) noexcept(noexcept(std::isgreater(v1.value(), v2.value())))
    {
        return std::isgreater(v1.value(), v2.value());
    }
    template<typename V, AngleType Base>
    inline constexpr bool isgreaterequal(Angle<V, Base> const& v1,
                                         Angle<V, Base> const& v2) noexcept(noexcept(std::isgreaterequal(v1.value(), v2.value())))
    {
        return std::isgreaterequal(v1.value(), v2.value());
    }
    template<typename V, AngleType Base>
    inline constexpr bool isless(Angle<V, Base> const& v1,
                                 Angle<V, Base> const& v2) noexcept(noexcept(std::isless(v1.value(), v2.value())))
    {
        return std::isless(v1.value(), v2.value());
    }
    template<typename V, AngleType Base>
    inline constexpr bool islessequal(Angle<V, Base> const& v1,
                                      Angle<V, Base> const& v2) noexcept(noexcept(std::islessequal(v1.value(), v2.value())))
    {
        return std::islessequal(v1.value(), v2.value());
    }
    template<typename V, AngleType Base>
    inline constexpr bool islessgreater(Angle<V, Base> const& v1,
                                        Angle<V, Base> const& v2) noexcept(noexcept(std::islessgreater(v1.value(), v2.value())))
    {
        return std::islessgreater(v1.value(), v2.value());
    }
    template<typename V, AngleType Base>
    inline constexpr bool isunordered(Angle<V, Base> const& v1,
                                      Angle<V, Base> const& v2) noexcept(noexcept(std::isunordered(v1.value(), v2.value())))
    {
        return std::isunordered(v1.value(), v2.value());
    }
}

#if _MSC_VER <= 1900
#pragma warning(pop)
#endif

#endif
