#include <gympl/testing.hpp>
#include <type_traits>

//#define GY_SANG_DISABLE_DEFINE_LITERALS
//#define GY_SANG_DISABLE_DEFINE_USINGS
#include <gysang/gysang.hpp>

namespace
{
    void basic_runtime_tests()
    {
        using namespace gysang;

        GYMPL_REQUIRE(Angle_DegD(2 * 360 + 1).valueAs0toFull() == 1);
        GYMPL_REQUIRE(Angle_DegD(-2 * 360 - 1).valueAs0toFull() == 359);

        GYMPL_REQUIRE(Angle_DegD(2 * 360 + 180 - 1).valueAsNegToPosHalf() == 179);
        GYMPL_REQUIRE(Angle_DegD(2 * 360 + 180 + 1).valueAsNegToPosHalf() == -179);
        GYMPL_REQUIRE(Angle_DegD(-2 * 360 - 180 - 1).valueAsNegToPosHalf() == 179);
        GYMPL_REQUIRE(Angle_DegD(-2 * 360 - 180 + 1).valueAsNegToPosHalf() == -179);

        auto d = 0._DegD;
        GYMPL_REQUIRE(d.value() == 0);
        d += 11._DegD;
        GYMPL_REQUIRE(d.value() == 11);
        d += Angle_RadD(M_PI);
        GYMPL_REQUIRE(d.value() == 191);

        auto dc(d);
        GYMPL_REQUIRE(dc.value() == 191);

        auto fr = []() -> Angle_DegD { return Angle_DegD{1}; };
        Angle_DegD const l(2);
        auto fl = [&l]() -> Angle_DegD const& { return l; };
        auto fx = []() -> Angle_DegD { return std::move(Angle_DegD{3}); };

        Angle_DegD i0cr(fr());
        GYMPL_REQUIRE(static_cast<double>(i0cr) == 1.);
        Angle_DegD i0cl(fl());
        GYMPL_REQUIRE(static_cast<double>(i0cl) == 2.);
        Angle_DegD i0cx(fx());
        GYMPL_REQUIRE(static_cast<double>(i0cx) == 3.);

        double dd = static_cast<double>(i0cx);
    }
}

GYMPL_TEST_MAIN_START
{
    basic_runtime_tests();
    return EXIT_SUCCESS;
}
GYMPL_TEST_MAIN_END
