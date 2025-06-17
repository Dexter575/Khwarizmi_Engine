#include "stop_watch/stop_watch.hpp"

#include <iostream>

#include "variant_lib/variant.hpp"

int main(int argc, char *argv[])
{
	std::cout<<"[KE:: Initializing.....]"<<std::endl;

    variant_lib::variant<int, double, std::string> myVar;

    myVar = 42;
    std::cout << "int: " << myVar.get<int>() << "\n";

	//myVar = 3.14;
    //std::cout << "double: " << myVar.get<double>() << "\n";

    //myVar = std::string("Hello, variant!");
    //std::cout << "string: " << myVar.get<std::string>() << "\n";

    // Use visitor pattern
    struct Printer {
        void operator()(int v) const { std::cout << "Visitor: int = " << v << "\n"; }
        void operator()(double v) const { std::cout << "Visitor: double = " << v << "\n"; }
        void operator()(const std::string& v) const { std::cout << "Visitor: string = " << v << "\n"; }
    };

    variant_lib::apply_visitor(Printer(), myVar);


	

	std::cout<<"[KE:: Terminating.....]"<<std::endl;
	return 0;
}