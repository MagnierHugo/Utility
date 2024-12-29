// Utility/main.cpp

#include <iostream>

#include "test.hpp"


int main(int argc, char* argv[]) {

    utl::TestClass obj{
        68, "Hello", true, 354, 213, 64684, 321, 32138
    };

    std::cout << "Default Get: " << obj.Default << '\n';
    std::cout << "Default Set: " << (obj.Default = 86) << '\n';
    std::cout << "ReadOnlyBasic Get: " << obj.ReadOnlyBasic << '\n';
    std::cout << "ReadOnlyBasic Set: " << (obj.ReadOnlyBasic = "Not supposed to work") << '\n'; // Works as expected
    std::cout << "ReadOnlyCustom Get: " << obj.ReadOnlyCustom << '\n';
    std::cout << "ReadOnlyCustom Set: " << (obj.ReadOnlyCustom = 42) << '\n'; // Works as expected
    std::cout << "WriteOnlyBasic Get: " << obj.WriteOnlyBasic << '\n'; // Works as expected
    std::cout << "WriteOnlyBasic Set: " << (obj.WriteOnlyBasic = false) << '\n'; // Works as expected
    std::cout << "WriteOnlyCustom Get: " << obj.WriteOnlyCustom << '\n'; // Works as expected
    std::cout << "WriteOnlyCustom Set: " << (obj.WriteOnlyCustom = 42.5f) << '\n'; // Works as expected
    std::cout << "ReadCustomWriteDefault Get: " << obj.ReadCustomWriteDefault << '\n';
    std::cout << "ReadCustomWriteDefault Set: " << (obj.ReadCustomWriteDefault = 300) << '\n';
    std::cout << "WriteCustomReadDefault Get: " << obj.WriteCustomReadDefault << '\n';
    std::cout << "WriteCustomReadDefault Set: " << (obj.WriteCustomReadDefault = 75) << '\n';
    std::cout << "FullCustom Get: " << obj.FullCustom << '\n';
    std::cout << "FullCustom Set: " << (obj.FullCustom = 12.67) << '\n';
    
    return 0;
}