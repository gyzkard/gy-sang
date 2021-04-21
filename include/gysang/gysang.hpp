/// \file gysang.hpp

#pragma once
#ifndef INCLUDED_GYSANG_GYSANG
// \cond macro-verbose-255
#define INCLUDED_GYSANG_GYSANG

#include <gympl/gympl.hpp>
#include <gympl/platform.hpp>

// \endcond

#include <algorithm>
#include <type_traits>
#ifdef GYMPL_HAS_SPACESHIP
#include <compare>
#endif

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
    enum AngleType
    {
        AngleType_Degree,
        AngleType_Radian
    };

    namespace angleTraits
    {
        template<typename V, AngleType Base>
        struct Constants;
        template<>
        struct Constants<float, AngleType_Degree>
        {
            static constexpr float half = 180.f;
            static constexpr float full = half * 2.f;
        };
        template<>
        struct Constants<double, AngleType_Degree>
        {
            static constexpr double half = 180.;
            static constexpr double full = half * 2.;
        };
        template<>
        struct Constants<long double, AngleType_Degree>
        {
            static constexpr long double half = 180.l;
            static constexpr long double full = half * 2.l;
        };
        template<>
        struct Constants<float, AngleType_Radian>
        {
            static constexpr float half = float(M_PI);
            static constexpr float full = half * 2.f;
        };
        template<>
        struct Constants<double, AngleType_Radian>
        {
            static constexpr double half = M_PI;
            static constexpr double full = half * 2.;
        };
        template<>
        struct Constants<long double, AngleType_Radian>
        {
            static constexpr long double half = (long double)(M_PI);
            static constexpr long double full = half * 2.l;
        };

        template<typename Vfrom, typename Vto, AngleType BaseFrom, AngleType BaseTo>
        struct Converter
        {
            static constexpr Vto convert(Vfrom value)
            {
                return static_cast<Vto>(value * Constants<Vto, BaseTo>::half / Constants<Vfrom, BaseFrom>::half);
            }
        };
        template<typename V, AngleType Base>
        struct Converter<V, V, Base, Base>
        {
            static constexpr V convert(V value)
            {
                return value;
            }
        };
        template<typename Vfrom, typename Vto, AngleType Base>
        struct Converter<Vfrom, Vto, Base, Base>
        {
            static constexpr Vto convert(Vfrom value)
            {
                return static_cast<Vto>(value);
            }
        };

        template<typename T, typename U, typename... V>
        struct BiggestResolution
        {
            typedef typename BiggestResolution<decltype(T() + U()), V...>::type type;
        };
        template<typename T, typename U>
        struct BiggestResolution<T, U>
        {
            typedef decltype(T() + U()) type;
        };
    }

    /// <summary>
    /// strong angle type
    /// </summary>
    /// <param name="V">underlying value type</param>
    /// <param name="Type">the value types basis value (only available with class non-type template parameters)</param>
    template<typename V, AngleType Base>
    struct Angle
    {
        template<typename VF, AngleType BaseF>
        friend struct Angle;

        using value_type = V;
        static constexpr AngleType angle_type = Base;

        using constants = angleTraits::Constants<V, Base>;

    private:
        V value_;

    public:
        explicit constexpr Angle(V v = V())
          : value_(v)
        {}

        template<typename OtherValue>
        explicit constexpr Angle(Angle<OtherValue, Base> const& o) noexcept
          : value_(o.value_)
        {}
        template<typename OtherValue>
        explicit constexpr Angle(Angle<OtherValue, Base>&& o) noexcept
          : value_(o.value_)
        {}

        template<typename OtherValue, AngleType OtherBase, typename std::enable_if<Base != OtherBase, bool>::type = true>
        explicit constexpr Angle(Angle<OtherValue, OtherBase> const& o) noexcept(
            noexcept(angleTraits::Converter<OtherValue, V, OtherBase, Base>::convert(o.value_)))
          : value_(angleTraits::Converter<OtherValue, V, OtherBase, Base>::convert(o.value_))
        {}
        template<typename OtherValue, AngleType OtherBase, typename std::enable_if<Base != OtherBase, bool>::type = true>
        explicit constexpr Angle(Angle<OtherValue, OtherBase>&& o) noexcept(
            noexcept(angleTraits::Converter<OtherValue, V, OtherBase, Base>::convert(o.value_)))
          : value_(angleTraits::Converter<OtherValue, V, OtherBase, Base>::convert(o.value_))
        {}

        Angle(Angle const& other) = default;
        Angle(Angle&& other) = default;

        Angle& operator=(Angle const&) = default;
        Angle& operator=(Angle&& other) = default;

        template<typename OtherValue>
        Angle& operator=(Angle<OtherValue, Base> const& o) noexcept
        {
            value_ = o.value_;
            return *this;
        }
        template<typename OtherValue>
        Angle& operator=(Angle<OtherValue, Base>&& o) noexcept
        {
            value_ = o.value_;
            return *this;
        }

        template<typename OtherValue, AngleType OtherBase, typename std::enable_if<Base != OtherBase, bool>::type = true>
        Angle& operator=(Angle<OtherValue, OtherBase> const& o) noexcept(
            noexcept(angleTraits::Converter<OtherValue, V, OtherBase, Base>::convert(o.value_)))
        {
            value_ = angleTraits::Converter<OtherValue, V, OtherBase, Base>::convert(o.value_);
            return *this;
        }
        template<typename OtherValue, AngleType OtherBase, typename std::enable_if<Base != OtherBase, bool>::type = true>
        Angle& operator=(Angle<OtherValue, OtherBase>&& o) noexcept(
            noexcept(angleTraits::Converter<OtherValue, V, OtherBase, Base>::convert(o.value_)))
        {
            value_ = angleTraits::Converter<OtherValue, V, OtherBase, Base>::convert(o.value_);
            return *this;
        }

        template<typename R, typename std::enable_if<std::is_floating_point<R>::value, bool>::type = true>
        explicit constexpr operator R() const noexcept(noexcept(static_cast<R>(value_)))
        {
            return static_cast<R>(value_);
        }

        constexpr Angle const& operator+() const noexcept
        {
            return *this;
        }
        constexpr Angle operator+(Angle const& o) const noexcept(noexcept(Angle(value_ + o.value_)))
        {
            return Angle(value_ + o.value_);
        }
        template<typename OtherValue>
        Angle& operator+=(Angle<OtherValue, Base> const& o) noexcept(noexcept(value_ += o.value_))
        {
            value_ += o.value_;
            return *this;
        }
        template<typename OtherValue, AngleType OtherBase, typename std::enable_if<Base != OtherBase, bool>::type = true>
        Angle& operator+=(Angle<OtherValue, OtherBase> o) noexcept(
            noexcept(value_ += angleTraits::Converter<OtherValue, V, OtherBase, Base>::convert(o.value_)))
        {
            value_ += angleTraits::Converter<OtherValue, V, OtherBase, Base>::convert(o.value_);
            return *this;
        }

        constexpr Angle operator-() const noexcept
        {
            return Angle(-value_);
        }
        constexpr Angle operator-(Angle const& o) const noexcept(noexcept(Angle(value_ - o.value_)))
        {
            return Angle(value_ - o.value_);
        }
        template<typename OtherValue>
        Angle& operator-=(Angle<OtherValue, Base> const& o) noexcept(noexcept(value_ -= o.value_))
        {
            value_ -= o.value_;
            return *this;
        }

        constexpr Angle operator*(Angle const& o) const noexcept(noexcept(Angle(value_* o.value_)))
        {
            return Angle(value_ * o.value_);
        }
        template<typename OtherValue>
        Angle& operator*=(Angle<OtherValue, Base> const& o) noexcept(noexcept(value_ *= o.value_))
        {
            value_ *= o.value_;
            return *this;
        }

        constexpr Angle operator/(Angle const& o) const noexcept(noexcept(Angle(value_ / o.value_)))
        {
            return Angle(value_ / o.value_);
        }
        template<typename OtherValue>
        Angle& operator/=(Angle<OtherValue, Base> const& o) noexcept(noexcept(value_ /= o.value_))
        {
            value_ /= o.value_;
            return *this;
        }

#ifdef GYMPL_HAS_SPACESHIP
        constexpr auto operator<=>(Angle const& other) const = default;
        template<typename OtherValue, AngleType OtherBase>
        requires(Base != OtherBase) constexpr auto operator<=>(Angle<OtherValue, OtherBase> const& other) const
            noexcept(noexcept(*this <=> Angle(other)))
        {
            return *this <=> Angle(other);
        }
#else
        constexpr bool operator!=(Angle const& other) const noexcept
        {
            return value_ != other.value_;
        }
        constexpr bool operator>=(Angle const& other) const noexcept
        {
            return value_ >= other.value_;
        }
        constexpr bool operator<=(Angle const& other) const noexcept
        {
            return value_ <= other.value_;
        }
        constexpr bool operator>(Angle const& other) const noexcept
        {
            return value_ > other.value_;
        }
        constexpr bool operator<(Angle const& other) const noexcept
        {
            return value_ < other.value_;
        }
#endif

        constexpr value_type value() const noexcept
        {
            return value_;
        }
#if _MSC_VER > 1900
        constexpr
#endif
            value_type&
            value() noexcept
        {
            return value_;
        }

        template<typename OtherValue, AngleType OtherBase>
        OtherValue constexpr valueAs() const
        {
            return angleTraits::Converter<V, OtherValue, Base, OtherBase>::convert(value_);
        }
        template<AngleType OtherBase>
        V constexpr valueAs() const
        {
            return angleTraits::Converter<V, V, Base, OtherBase>::convert(value_);
        }

        value_type valueAs0toFull() const
        {
            auto constexpr const full = constants::full;

            return std::fmod(std::fmod(value_, full) + full, full);
        }
        value_type valueAsNegToPosHalf() const
        {
            auto constexpr const half = constants::half;
            auto constexpr const full = constants::full;

            value_type ret = valueAs0toFull();
            return ret <= half ? ret : -full + ret;
        }

        Angle as0toFull() const
        {
            return Angle(valueAs0toFull());
        }
        Angle asNegToPosHalf() const
        {
            return Angle(valueAsNegToPosHalf());
        }
    };

#ifndef GYMPL_HAS_DEFINITIONLESS_STATIC_CONSTEXPR_DATA_MEMBER
    template<typename V, AngleType Base>
    constexpr AngleType Angle<V, Base>::angle_type;
#endif

    template<typename Vleft, typename Vright, AngleType BaseLeft, AngleType BaseRight>
    constexpr Angle<typename angleTraits::BiggestResolution<Vleft, Vright>::type, BaseLeft> operator+(
        Angle<Vleft, BaseLeft> const& left,
        Angle<Vright, BaseRight> const& right) noexcept(noexcept(left + Angle<Vleft, BaseLeft>(right)))
    {
        return left + Angle<Vleft, BaseLeft>(right);
    }
    template<typename Vleft, typename Vright, AngleType BaseLeft, AngleType BaseRight>
    constexpr Angle<typename angleTraits::BiggestResolution<Vleft, Vright>::type, BaseLeft> operator-(
        Angle<Vleft, BaseLeft> const& left,
        Angle<Vright, BaseRight> const& right) noexcept(noexcept(left - Angle<Vleft, BaseLeft>(right)))
    {
        return left - Angle<Vleft, BaseLeft>(right);
    }
    template<typename Vleft, typename Vright, AngleType BaseLeft, AngleType BaseRight>
    constexpr Angle<typename angleTraits::BiggestResolution<Vleft, Vright>::type, BaseLeft> operator*(
        Angle<Vleft, BaseLeft> const& left, Angle<Vright, BaseRight> const& right) noexcept(noexcept(left* Angle<Vleft, BaseLeft>(right)))
    {
        return left * Angle<Vleft, BaseLeft>(right);
    }
    template<typename Vleft, typename Vright, AngleType BaseLeft, AngleType BaseRight>
    constexpr Angle<typename angleTraits::BiggestResolution<Vleft, Vright>::type, BaseLeft> operator/(
        Angle<Vleft, BaseLeft> const& left,
        Angle<Vright, BaseRight> const& right) noexcept(noexcept(left / Angle<Vleft, BaseLeft>(right)))
    {
        return left / Angle<Vleft, BaseLeft>(right);
    }

    template<typename Vleft, typename Vright, AngleType BaseLeft, AngleType BaseRight>
    constexpr bool operator==(Angle<Vleft, BaseLeft> const& left,
                              Angle<Vright, BaseRight> const& right) noexcept(noexcept(left.value() ==
                                                                                       right.template valueAs<Vleft, BaseLeft>()))
    {
        return left.value() == right.template valueAs<Vleft, BaseLeft>();
    }

#ifndef GY_SANG_DISABLE_DEFINE_LITERALS
/// <summary>
/// define a user defined literal for a Angle with specific \ref angle and value type
/// </summary>
/// <param name="mp_valueType">value type</param>
/// <param name="mp_angleType">angle type</param>
/// <param name="mp_literal">literal name</param>
#define GY_SANG_DEFINE_LITERAL(mp_valueType, mp_angleType, mp_literal)                         \
    inline constexpr Angle<mp_valueType, mp_angleType> operator"" _##mp_literal(long double v) \
    {                                                                                          \
        return Angle<mp_valueType, mp_angleType>(static_cast<mp_valueType>(v));                \
    }
#endif

#ifndef GY_SANG_DISABLE_DEFINE_USINGS
/// <summary>
/// define a typedef for a Angle with specific \ref angle and value type
/// </summary>
/// <param name="mp_valueType">value type</param>
/// <param name="mp_angleType">angle type</param>
/// <param name="mp_literal">literal name</param>
#define GY_SANG_DEFINE_USING(mp_valueType, mp_angleType, mp_literal) using Angle_##mp_literal = Angle<mp_valueType, mp_angleType>
#endif

/// <summary>
/// define a typedef and a user defined literal for a specific \ref Indexed type instance for bases zero and one
/// </summary>
/// <param name="mp_valueType">value type</param>
/// <param name="mp_angleType">angle type</param>
/// <param name="mp_literal">literal name</param>
#define GY_SANG_DEFINE_ALL(mp_valueType, mp_angleType, mp_literal)  \
    GY_SANG_DEFINE_LITERAL(mp_valueType, mp_angleType, mp_literal); \
    GY_SANG_DEFINE_USING(mp_valueType, mp_angleType, mp_literal);

    GY_SANG_DEFINE_ALL(float, AngleType::AngleType_Degree, DegF);
    GY_SANG_DEFINE_ALL(double, AngleType::AngleType_Degree, DegD);
    GY_SANG_DEFINE_ALL(long double, AngleType::AngleType_Degree, DegL);
    GY_SANG_DEFINE_ALL(float, AngleType::AngleType_Radian, RadF);
    GY_SANG_DEFINE_ALL(double, AngleType::AngleType_Radian, RadD);
    GY_SANG_DEFINE_ALL(long double, AngleType::AngleType_Radian, RadL);
}

#if _MSC_VER <= 1900
#pragma warning(pop)
#endif

#endif
