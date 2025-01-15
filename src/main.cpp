// Utility/main.cpp

#include <iostream>

#include "test.hpp"
#include "Maths/matrix.hpp"


int main(int argc, char* argv[]) {

    // utl::TestClass test{32};

    // test.GetSetLog(test.Internal, "Internal Default");

    // test.GetSetLog(test.External, "External Default");
    // test.LogExternal();

    // utl::Matrix<float, 1, 4> matrix;

    int var = 3;
    _ = var;

    std::cout << "Var after voided: " << var << '\n';

    int test = 4;
    std::ignore = test;
    
    return 0;
}