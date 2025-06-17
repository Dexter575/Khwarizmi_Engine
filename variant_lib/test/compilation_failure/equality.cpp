// @EXPECTED:

#include <variant_lib/variant.hpp>

int main()
{
    variant_lib::variant<int> x;
    variant_lib::variant<double> y;
    x == y;
}
