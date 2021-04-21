#include <cassert>

//#define GY_SANG_DISABLE_DEFINE_LITERALS
//#define GY_SANG_DISABLE_DEFINE_USINGS
#include <gysang/cmath.hpp>
#include <gysang/gysang.hpp>

namespace
{
    using namespace gysang;

    void example()
    {
		Angle_DegD d(-30);
		Angle_RadD r(d);
		double f = std::abs(sin(d) / cos(r) - tan(r));
		if (std::abs(sin(d) / cos(r) - tan(r)) < 1e-15)
			d = abs(d);
		assert(d.value() == 30);
    }
}

int main()
{
    example();
    return EXIT_SUCCESS;
}
