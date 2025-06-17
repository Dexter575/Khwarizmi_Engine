// @EXPECTED: no matching function for call to .*\<apply_visitor\>

#include <variant_lib/variant.hpp>

struct mutating_visitor
{
    mutating_visitor(int val)
        : val_(val) {}

    void operator()(int& val) const
    {
        val = val_;
    }

    int val_;
};

int main()
{
    const variant_lib::variant<int> var(123);
    const mutating_visitor visitor(456);
    variant_lib::apply_visitor(visitor, var);
}
