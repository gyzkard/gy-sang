#include <cfenv>
#include <gympl/testing.hpp>
#include <type_traits>

//#define GY_SANG_DISABLE_DEFINE_LITERALS
//#define GY_SANG_DISABLE_DEFINE_USINGS
#include <gysang/cmath.hpp>
#include <gysang/gysang.hpp>

namespace
{
    void cmath_runtime_tests()
    {
        using namespace gysang;

        GYMPL_REQUIRE(abs(Angle_DegD(11)).value() == 11);
        GYMPL_REQUIRE(abs(Angle_DegD(-11)).value() == 11);
        GYMPL_REQUIRE(abs(Angle_RadD(11)).value() == 11);
        GYMPL_REQUIRE(abs(Angle_RadD(-11)).value() == 11);
        GYMPL_REQUIRE(fabs(Angle_DegD(11)).value() == 11);

        GYMPL_REQUIRE(fmod(Angle_DegD(11), 4).value() == 3);
        GYMPL_REQUIRE(remainder(Angle_DegD(11.5), 4).value() == -.5);
        {
            int quo;
            GYMPL_REQUIRE(remquo(Angle_DegD(11.5), 4, &quo).value() == -.5);
            GYMPL_REQUIRE(quo == 3);
        }
        GYMPL_REQUIRE(fma(Angle_DegD(2), 3, Angle_RadD(M_PI)).value() == 186);

        GYMPL_REQUIRE(max(Angle_DegD(11), Angle_DegD(10)).value() == 11);
        GYMPL_REQUIRE(max(Angle_DegD(11), Angle_DegD(12)).value() == 12);
        GYMPL_REQUIRE(max(Angle_DegD(11), Angle_RadD(M_PI)).value() == 180);
        GYMPL_REQUIRE(max(Angle_DegD(11), Angle_RadD(-M_PI)).value() == 11);
        GYMPL_REQUIRE(min(Angle_DegD(11), Angle_DegD(10)).value() == 10);
        GYMPL_REQUIRE(min(Angle_DegD(11), Angle_DegD(12)).value() == 11);
        GYMPL_REQUIRE(min(Angle_DegD(11), Angle_RadD(M_PI)).value() == 11);
        GYMPL_REQUIRE(min(Angle_DegD(11), Angle_RadD(-M_PI)).value() == -180);

        GYMPL_REQUIRE(fdim(Angle_DegD(11), Angle_DegD(10)).value() == 1);
        GYMPL_REQUIRE(fdim(Angle_DegD(11), Angle_DegD(12)).value() == 0);
        GYMPL_REQUIRE(fdim(Angle_DegD(11), Angle_RadD(M_PI)).value() == 0);
        GYMPL_REQUIRE(fdim(Angle_DegD(11), Angle_RadD(-M_PI)).value() == 191);

#if defined(GYMPL_HAS_LERP)
        GYMPL_REQUIRE(lerp(Angle_DegD(10), Angle_DegD(20), .1).value() == 11);
        GYMPL_REQUIRE(lerp(Angle_DegD(10), Angle_DegD(20), -.1).value() == 9);
        GYMPL_REQUIRE(lerp(Angle_DegD(0), Angle_RadD(M_PI), 1.5).value() == 270);
#endif

        GYMPL_REQUIRE(sin(Angle_DegD(90)) == 1);
        GYMPL_REQUIRE(sin(Angle_RadD(M_PI / 2.)) == 1);
        GYMPL_REQUIRE(cos(Angle_DegD(180)) == -1);
        GYMPL_REQUIRE(cos(Angle_RadD(M_PI)) == -1);
        GYMPL_REQUIRE(gympl::testing::isEqual(tan(Angle_DegD(45)), 1., 1e-15));
        GYMPL_REQUIRE(gympl::testing::isEqual(tan(Angle_RadD(M_PI / 4.)), 1., 1e-15));

        GYMPL_REQUIRE(std::fegetround() == std::float_round_style::round_toward_zero);
        GYMPL_REQUIRE(ceil(Angle_DegD(2.5)) == Angle_DegD(3));
        GYMPL_REQUIRE(ceil(Angle_RadD(2.5)) == Angle_RadD(3));
        GYMPL_REQUIRE(floor(Angle_DegD(2.5)) == Angle_DegD(2));
        GYMPL_REQUIRE(floor(Angle_RadD(2.5)) == Angle_RadD(2));
        GYMPL_REQUIRE(trunc(Angle_DegD(2.5)) == Angle_DegD(2));
        GYMPL_REQUIRE(trunc(Angle_RadD(2.5)) == Angle_RadD(2));
        GYMPL_REQUIRE(round(Angle_DegD(2.5)) == Angle_DegD(3));
        GYMPL_REQUIRE(round(Angle_RadD(2.5)) == Angle_RadD(3));
        GYMPL_REQUIRE(nearbyint(Angle_DegD(2.5)) == Angle_DegD(2));
        GYMPL_REQUIRE(nearbyint(Angle_RadD(2.5)) == Angle_RadD(2));
        GYMPL_REQUIRE(rint(Angle_DegD(2.5)) == Angle_DegD(2));
        GYMPL_REQUIRE(rint(Angle_RadD(2.5)) == Angle_RadD(2));
        GYMPL_REQUIRE(ceil(Angle_DegD(-2.5)) == -Angle_DegD(2));
        GYMPL_REQUIRE(ceil(Angle_RadD(-2.5)) == -Angle_RadD(2));
        GYMPL_REQUIRE(floor(Angle_DegD(-2.5)) == -Angle_DegD(3));
        GYMPL_REQUIRE(floor(Angle_RadD(-2.5)) == -Angle_RadD(3));
        GYMPL_REQUIRE(round(Angle_DegD(-2.5)) == -Angle_DegD(3));
        GYMPL_REQUIRE(round(Angle_RadD(-2.5)) == -Angle_RadD(3));
        GYMPL_REQUIRE(nearbyint(Angle_DegD(-2.5)) == -Angle_DegD(2));
        GYMPL_REQUIRE(nearbyint(Angle_RadD(-2.5)) == -Angle_RadD(2));
        GYMPL_REQUIRE(rint(Angle_DegD(-2.5)) == -Angle_DegD(2));
        GYMPL_REQUIRE(rint(Angle_RadD(-2.5)) == -Angle_RadD(2));

        GYMPL_REQUIRE(fpclassify(Angle_DegD()) == FP_ZERO);
        GYMPL_REQUIRE(! isfinite(Angle_DegD(std::numeric_limits<double>::infinity())));
        GYMPL_REQUIRE(isinf(Angle_DegD(std::numeric_limits<double>::infinity())));
        GYMPL_REQUIRE(isnan(Angle_DegD(std::numeric_limits<double>::quiet_NaN())));
        GYMPL_REQUIRE(! isnormal(Angle_DegD(std::numeric_limits<double>::denorm_min())));
        GYMPL_REQUIRE(signbit(Angle_DegD(-1)));
        GYMPL_REQUIRE(isgreater(1._DegD, 0._DegD));
        GYMPL_REQUIRE(isgreaterequal(1._DegD, 0._DegD));
        GYMPL_REQUIRE(isgreaterequal(1._DegD, 1._DegD));
        GYMPL_REQUIRE(isless(1._DegD, 2._DegD));
        GYMPL_REQUIRE(islessequal(1._DegD, 2._DegD));
        GYMPL_REQUIRE(islessequal(1._DegD, 1._DegD));
        GYMPL_REQUIRE(! islessgreater(1._DegD, 1._DegD));
        GYMPL_REQUIRE(! isunordered(1._DegD, 1._DegD));
    }
}

GYMPL_TEST_MAIN_START
{
    cmath_runtime_tests();
    return EXIT_SUCCESS;
}
GYMPL_TEST_MAIN_END
