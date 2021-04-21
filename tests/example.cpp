#include <cassert>
#include <gympl/outputCompilerInfo.hpp>
#include <gympl/testing.hpp>

//#define GY_SANG_DISABLE_DEFINE_LITERALS
//#define GY_SANG_DISABLE_DEFINE_USINGS
#include <gysang/cmath.hpp>
#include <gysang/gysang.hpp>

#define GYMPL_PRINT_CONFIG
#include <gympl/outputConfiguration.hpp>

namespace
{
    void example1()
    {
        using namespace gysang;

        //! [example1]
        Angle_DegD d(-30);
        Angle_RadD r(d);
        double f = std::abs(sin(d) / cos(r) - tan(r));
        if (std::abs(sin(d) / cos(r) - tan(r)) < 1e-15)
            d = abs(d);
        assert(d.value() == 30);
        //! [example1]
    }
}

GYMPL_TEST_MAIN_START
{
    example1();
    return EXIT_SUCCESS;
}
GYMPL_TEST_MAIN_END
