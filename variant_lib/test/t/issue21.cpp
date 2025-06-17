#include "catch.hpp"

#include <variant_lib/variant.hpp>
#include <variant_lib/variant_io.hpp>

// https://c/variant/issues/21

static int count;

struct t1
{
    int value;

    t1(t1 const& rhs)
        : value(rhs.value)
    {
        ++count;
    }
    t1(int v) : value(v)
    {
        ++count;
    }
    ~t1()
    {
        --count;
    }
};

struct t2
{
    int value;
    t2(int v) : value(v)
    { // constructor fails
        throw std::runtime_error("fail");
    }
};

TEST_CASE("set() works cleanly even if the constructor throws ", "[variant]")
{

    using variant_type = variant_lib::variant<t1, t2>;

    count = 0;
    {
        t1 obj{42};
        variant_type v = obj;
        REQUIRE(v.is<t1>());
        REQUIRE(v.get<t1>().value == 42);
        REQUIRE_THROWS(v.set<t2>(13));
    }
    REQUIRE(count == 0);
}
