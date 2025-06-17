#include <variant_lib/variant.hpp>

#include <stdexcept>

struct check
{
    template <typename T>
    void operator()(T const& val) const
    {
        if (val != 0) throw std::runtime_error("invalid");
    }
};

int main()
{
    typedef variant_lib::variant<bool, int, double> variant_type;
    variant_type v(0);
    variant_lib::apply_visitor(check(), v);
    return 0;
}
