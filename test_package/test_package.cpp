//#define GY_SANG_DISABLE_DEFINE_LITERALS
//#define GY_SANG_DISABLE_DEFINE_USINGS
#include <gysang/gysang.hpp>

#include <cassert>

namespace
{
    using namespace gysang;

    void example()
    {
        assert(2 * 2 == 4);
        assert(2 * 2_i1 == 4_i1);
        assert(2_i1 * 2 == 4_i1);
        assert(2 * 2_i1 == 3);
        assert(2_i1 * 2 == 3);

        int data[] = { 2, 3 };
        int sum = 0;
        for (auto i = 1_i1; i <= Indexed_i1{ sizeof(data)/sizeof(int) }; ++i)
            sum += data[i]*static_cast<int>(i);

        assert(sum == 3); // 2*0 + 3*1
    }
}

int main()
{
    example();
    return EXIT_SUCCESS;
}
