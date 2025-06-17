#include "catch.hpp"

#include <variant_lib/variant.hpp>
#include <variant_lib/variant_io.hpp>

#include <string>

TEST_CASE("variant_alternative", "[types]")
{
    using variant_type =  variant_lib::variant<int, double, std::string>;
    using type_0 = variant_lib::variant_alternative<0, variant_type>::type;
    using type_1 = variant_lib::variant_alternative<1, variant_type>::type;
    using type_2 = variant_lib::variant_alternative<2, variant_type>::type;
    //using type_3 = variant_lib::variant_alternative<3, variant_type>::type; // compile error
    constexpr bool check_0 = std::is_same<int, type_0>::value;
    constexpr bool check_1 = std::is_same<double, type_1>::value;
    constexpr bool check_2 = std::is_same<std::string, type_2>::value;
    CHECK(check_0);
    CHECK(check_1);
    CHECK(check_2);
}

TEST_CASE("variant_size", "[types]")
{
    constexpr auto value_0 = variant_lib::variant_size<variant_lib::variant<>>::value;
    constexpr auto value_1 = variant_lib::variant_size<variant_lib::variant<int>>::value;
    constexpr auto value_2 = variant_lib::variant_size<variant_lib::variant<int, std::string>>::value;
    CHECK(value_0 == 0);
    CHECK(value_1 == 1);
    CHECK(value_2 == 2);
}
