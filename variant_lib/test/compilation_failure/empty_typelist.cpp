// @EXPECTED: Template parameter type list of variant can not be empty

#include <variant_lib/variant.hpp>

// Empty type list should not work.

int main()
{
    variant_lib::variant<> x;
}
