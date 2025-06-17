// @EXPECTED: First type in variant must be default constructible to allow default construction of variant

#include <variant_lib/variant.hpp>

// Checks that the first type in a variant must be default constructible to
// make the variant default constructible.

struct no_def_constructor
{

    int value;

    no_def_constructor() = delete;

    no_def_constructor(int v) : value(v) {}
};

int main()
{
    variant_lib::variant<no_def_constructor> x;
}
