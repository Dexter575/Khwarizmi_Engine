#include "stop_watch/stop_watch.hpp"

#include <iostream>
#include <variant>
#include "variant_lib/variant.hpp"

#include "parser/ExpressionParser.h"

#include <type_traits>
#include <concepts>
#include <functional>

#include <cxxabi.h>
#include <memory>
#include <typeinfo>

/* this helper function is to human-readable name from data type when using typeid(T).name */
std::string demangle(const char* mangled) {
    int status = 0;
    std::unique_ptr<char, void(*)(void*)>  
        demangled{ abi::__cxa_demangle(mangled, nullptr, nullptr, &status),
                   std::free };
    return (status==0 && demangled) ? demangled.get() : mangled;
}

template<typename T>
concept ArithmeticExpression = (std::integral<T> && !std::same_as<T, bool>) || std::floating_point<T>;

template<typename T, typename U, typename Op>
concept BinaryExpressionType = ArithmeticExpression<T> && ArithmeticExpression<U>
                            && requires(T a, U b, Op op) { { op(a, b) } -> std::convertible_to<decltype(op(a, b))>; };

struct MapInfo {
    std::size_t road_id = 5;
    float s_value = 5.5f;
    MapInfo() { };
};

/*
bool operator>(const MapInfo& m, const MapInfo& n) {
    std::cout<<"I was Executed from MapInfo overloaded operator"<<std::endl;
    return false;
};
*/

//bool operator>(const MapInfo& m, const bool& b) = delete;
using ReturnType = variant_lib::variant<
    int,          // 1  
    double,       // 0
    std::size_t,  // 2
    bool,         // 3
    float,        // 4
    MapInfo,      // 5
    std::string   // 6
>;

struct ArithemticOpEvaluation {
    // static
    // 1) The “good” overload, only when the operation is valid.
    template<typename T, typename U, typename Op>
        requires BinaryExpressionType<T, U, Op>
    ReturnType operator()(T a, U b, Op op) const {
        // compute once
        return op(a, b); // R = decltype(a+b)
    };

    // fallback.
    template<typename T, typename U, typename Op>
    ReturnType operator()(T a, U b, Op op) const {
        throw std::invalid_argument("Bad Operand Types for: "
            "Operand 1: " + demangle(typeid(T).name()) +
            " with operator: " + demangle(typeid(Op).name()) + 
            " Operand 2: " + demangle(typeid(U).name()) );
        return {true};
    };
};

template<typename Op>
auto MakeArithmeticVisitor(Op op) {
    return [op](const auto & first, const auto& second) {
        return ArithemticOpEvaluation{}(first, second, op);
    };
};

auto ADD      = MakeArithmeticVisitor(std::plus<>{});
auto SUBTRACT = MakeArithmeticVisitor(std::minus<>{});
auto MULTIPLY = MakeArithmeticVisitor(std::multiplies<>{});
auto DIVIDE   = MakeArithmeticVisitor(std::divides<>{});




namespace variant_lib {

template<typename T>
constexpr bool IsRealArithmetic = std::is_arithmetic_v<T>;

template<typename T, typename U, typename Cmp>
concept HasOverload = requires(T a, U b, Cmp cmp) {
    { cmp(a, b) } -> std::convertible_to<bool>;
};


bool compare_variant()


bool operator>(ReturnType const& lhs, ReturnType const& rhs) {
    return apply_visitor(
      // we need [&] so we can see lhs/rhs
      [&](auto const& x, auto const& y) -> bool {
        using X = std::decay_t<decltype(x)>;
        using Y = std::decay_t<decltype(y)>;

        if constexpr ( (IsRealArithmetic<X> && IsRealArithmetic<Y>) || (HasOverload<X, Y,  ) ) {
          // numeric compare for arithmetic OR same type, and that type has operator< → use it
          return x > y;
        }
        else {
            // PLEASE NOTE: the default behaviour of vairant is to return via index ordering that is: lhs.which() > rhs.which();
            // for us, we just return false;
            return false;
        }
      },
      lhs, rhs
    );
}

}; // namespace variant_lib


int main(int argc, char *argv[])
{
	std::cout<<"[KE:: Initializing.....]"<<std::endl;

    variant_lib::variant<int, double, std::string> myVar;

    // Use visitor pattern
    struct Printer {
        void operator()(int v) const { std::cout << "Visitor: int = " << v << "\n"; }
        void operator()(double v) const { std::cout << "Visitor: double = " << v << "\n"; }
        void operator()(const std::string& v) const { std::cout << "Visitor: string = " << v << "\n"; }
        void operator()(const std::size_t& v) const { std::cout << "Visitor: std::size_t = " << v << "\n"; }
        void operator()(bool v) const { std::cout << "Visitor: bool = " << v << "\n"; }
        void operator()(float v) const { std::cout << "Visitor: float = " << v << "\n"; }
        void operator()(const MapInfo& v) const { std::cout << "Visitor: float = " << v.road_id << "\n"; }
    };

    // variables.
    ReturnType a = 42;  // holds double (index 0)
    ReturnType b = 6;  // holds int    (index 1)


    /*
    auto ADD = [&](const auto& first, const auto& second) {
        return ArithemticOpEvaluation{ }(first, second, std::plus<>{ });
    };

    auto SUBTRACT = [&](const auto& first, const auto& second) {
        return ArithemticOpEvaluation{ }(first, second, std::minus<>{ });
    };

    auto MULTIPLY = [&](const auto& first, const auto& second) {
        return ArithemticOpEvaluation{ }(first, second, std::multiplies<>{ });
    };

    auto DIVIDE = [&](const auto& first, const auto& second) {
        return ArithemticOpEvaluation{ }(first, second, std::divides<>{ });
    };
    */

    ReturnType return_value;
    try {
        return_value  = variant_lib::apply_visitor(MakeArithmeticVisitor(std::plus<>{}), a, b);
    }  
    catch (std::invalid_argument& e) {
        std::cerr << "Operation failed: " << e.what() << "\n";
    }

    //Comparison...
    ReturnType d = 5.5;      // holds double (index 1)
    ReturnType e = 3.5;    // holds int    (index 0)

    //ReturnType c = d > e; / true, because 5 > 3.5 numerically
    ReturnType c = d > e;  // true, because 5 > 3.5 numerically
    ReturnType false_c = d > e;
    

    ReturnType alpha_1 = MapInfo();
    ReturnType alpha_2 = MapInfo();

    ReturnType alpha_3 = alpha_1 > alpha_2;

    variant_lib::apply_visitor(Printer(), alpha_3);


   // variant_lib::apply_visitor(Printer(), return_value);

	std::cout<<"[KE:: Terminating.....]"<<std::endl;
	return 0;
}