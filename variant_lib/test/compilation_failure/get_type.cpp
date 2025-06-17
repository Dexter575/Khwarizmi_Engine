// @EXPECTED: no matching .*\<function for call to .*\<get\>

#include <variant_lib/variant.hpp>

int main()
{
    variant_lib::variant<int, double> x;
    x.get<std::string>();
}
