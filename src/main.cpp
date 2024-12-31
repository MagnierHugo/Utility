// Utility/main.cpp

#include <iostream>

#include "test.hpp"


int main(int argc, char* argv[]) {

    utl::TestClass test{32};

    test.GetSetLog(test.Internal, "Internal Default");

    test.GetSetLog(test.External, "External Default");
    test.LogExternal();
    
    return 0;
}