// @EXPECTED: Variant can not hold reference types

#include <variant_lib/variant.hpp>

int main()
{
    variant_lib::variant<double, int&, long> x{variant_lib::no_init()};
}
