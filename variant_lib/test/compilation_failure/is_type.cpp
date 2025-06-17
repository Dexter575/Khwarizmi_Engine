// @EXPECTED:

#include <variant_lib/variant.hpp>

int main()
{
    variant_lib::variant<int, double> x;
    x.is<std::string>();
}
