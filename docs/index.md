<!---
Copyright 2021-today gyzkard
(gyzkard@gyzkard.com)

Distributed under the MIT License.
(https://opensource.org/licenses/mit-license.php)
-->

gy-sang
=======

Strong types to distinguish between degree and radian and possibly other types.

## Copyright and License

* Copyright 2021-today gyzkard (gyzkard@gyzkard.com)

Distributed under the MIT License 
(https://opensource.org/licenses/mit-license.php).


## Basic Usage

```cpp
#include <gysang/gysang.hpp>

using namespace gysang;

Angle_DegD d(-30);
Angle_RadD r(d);
double f = std::abs(sin(d) / cos(r) - tan(r));
if (std::abs(sin(d) / cos(r) - tan(r)) < 1e-15)
	d = abs(d);
assert(d.value() == 30);
```

## Predefined types and literals

User defined literals and typedef are defined for all combinations of built-in floating point types and angle types degree and radian.

They're are defined using the macro \ref GY_SANG_DEFINE_ALL at the end of \ref gysang.hpp.

You can opt out of this by defining \ref GY_SANG_DISABLE_DEFINE_LITERALS or \ref GY_SANG_DISABLE_DEFINE_USINGS before including \ref gysang.hpp.


F.e. for int and base zero, that's type `Indexed_i0` and literal `_i0`.

These are all the types:
- `float degree`, DegF
- `double degree`, DegD
- `long double degree`, DegL
- `float radian`, RadF
- `double radian`, RadD
- `long double radian`, RadL
