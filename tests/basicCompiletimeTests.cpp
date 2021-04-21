#include <gympl/testing.hpp>
#include <type_traits>

//#define GY_SANG_DISABLE_DEFINE_LITERALS
//#define GY_SANG_DISABLE_DEFINE_USINGS
#include <gysang/gysang.hpp>

namespace
{
    void basic_compiletime_tests()
    {
        using namespace gysang;

        static_assert(Angle_DegD(360) == Angle_RadD(M_PI * 2.) GYMPL_NTSA);

        static_assert(std::is_same<decltype(Angle_DegF() + Angle_DegF())::value_type, float>::value GYMPL_NTSA);
        static_assert(std::is_same<decltype(Angle_DegD() + Angle_DegD())::value_type, double>::value GYMPL_NTSA);
        static_assert(std::is_same<decltype(Angle_DegL() + Angle_DegL())::value_type, long double>::value GYMPL_NTSA);
        static_assert(std::is_same<decltype(Angle_DegF() + Angle_DegD())::value_type, double>::value GYMPL_NTSA);
        static_assert(std::is_same<decltype(Angle_DegD() + Angle_DegF())::value_type, double>::value GYMPL_NTSA);
        static_assert(std::is_same<decltype(Angle_DegF() + Angle_DegL())::value_type, long double>::value GYMPL_NTSA);
        static_assert(std::is_same<decltype(Angle_DegL() + Angle_DegF())::value_type, long double>::value GYMPL_NTSA);
        static_assert(std::is_same<decltype(Angle_DegD() + Angle_DegL())::value_type, long double>::value GYMPL_NTSA);
        static_assert(std::is_same<decltype(Angle_DegL() + Angle_DegD())::value_type, long double>::value GYMPL_NTSA);

        static_assert(Angle_DegD() == Angle_RadD() GYMPL_NTSA);
        static_assert(Angle_DegD() == Angle_RadD(0) GYMPL_NTSA);
        static_assert(Angle_DegD(0) == Angle_RadD() GYMPL_NTSA);
        static_assert(Angle_DegD(0) == Angle_RadD(0) GYMPL_NTSA);

        static_assert(1._DegD <= 1._DegD GYMPL_NTSA);
        static_assert(1._DegD <= 2._DegD GYMPL_NTSA);
        static_assert(1._DegD < 2._DegD GYMPL_NTSA);
        static_assert(1._DegD >= 1._DegD GYMPL_NTSA);
        static_assert(1._DegD >= 0._DegD GYMPL_NTSA);
        static_assert(1._DegD > 0._DegD GYMPL_NTSA);
    }
}

GYMPL_TEST_MAIN_START
{
    return EXIT_SUCCESS;
}
GYMPL_TEST_MAIN_END
