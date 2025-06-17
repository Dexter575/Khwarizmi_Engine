
#include "catch.hpp"

#include <variant_lib/variant.hpp>
#include <variant_lib/variant_io.hpp>

#include <string>

template <typename T>
struct mutating_visitor
{
    mutating_visitor(T& val)
        : val_(val) {}

    void operator()(T& val) const
    {
        val = val_;
    }

    template <typename T1>
    void operator()(T1&) const
    {
    } // no-op

    T& val_;
};

TEST_CASE("variant visitation", "[visitor][unary visitor]")
{
    variant_lib::variant<int, double, std::string> var(123);
    REQUIRE(var.get<int>() == 123);
    int val = 456;
    const mutating_visitor<int> visitor(val);
    variant_lib::apply_visitor(visitor, var);
    REQUIRE(var.get<int>() == 456);
}
