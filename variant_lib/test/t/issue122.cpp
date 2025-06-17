#include "catch.hpp"

#include <variant_lib/variant.hpp>
#include <variant_lib/variant_io.hpp>

// https://github.com/mapbox/variant/issues/122

struct X
{
    template <typename ValueType>
    X(const ValueType&)  {}
};


TEST_CASE("Correctly choose appropriate constructor", "[variant]")
{
    variant_lib::variant<X, int> a{123};
    decltype(a) b(a);
    REQUIRE(a.which() == b.which());
}
