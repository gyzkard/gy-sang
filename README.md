# gy-sang

Strong angle types for C++ to distinguish between degree and radian and possibly other types.

## Quickstart

```c++
#include <gysang/gysang.hpp>

using namespace gysang;

Angle_DegD d(-30);
Angle_RadD r(d);
double f = std::abs(sin(d) / cos(r) - tan(r));
if (std::abs(sin(d) / cos(r) - tan(r)) < 1e-15)
	d = abs(d);
assert(d.value() == 30);
```

## Supported compilers

At the moment, this library requires C++11 support.
It has been successfully tested with
* MSVC V16.9.2 (VS 2019) V15.9.34 (VS 2017), mostly V14.0.25431.01 Update 3 (VS 2015) [some traits don't work yet]; VS 2010 and below won't work
* clang 7.0.1-8 and 11.0.1-2
* gcc 8.3.0-6 and 10.2.1-6
