// Utility/main.cpp

#include <iostream>

#include "test.hpp"
#include "Maths/matrix.hpp"


int main(int argc, char* argv[]) {

    // utl::TestClass test{32};

    // test.GetSetLog(test.Internal, "Internal Default");

    // test.GetSetLog(test.External, "External Default");
    // test.LogExternal();

    int values[20] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
        10, 11, 12, 13, 14, 15, 16, 17, 18, 19
    };

    utl::IntervalSpan<int> span{values, &values[10]};
    utl::IntervalSpan<int> span2{&values[10], &values[20], 2};
    std::cout << span << '\n';
    std::cout << span2 << "\n\n";

    utl::Matrix<int, 3, 3> m{0, 1, 2, 3, 4, 5, 6, 7, 8};
    std::cout << m << '\n';

    std::array<int, 3> a1{0, 1, 2};
    std::array<int, 3> a2{3, 4, 5};
    std::array<int, 3> a3{6, 7, 8};
    std::array<int, 3> a4{9, 10, 11};
    std::array<int, 3> a5{12, 13, 14};
    utl::Matrix<int, 5, 3> m2{a1, a2, a3, a4, a5};
    std::cout << m2 << '\n';

    auto m3 = m2 * m;
    std::cout << m3 << '\n';
    
    return 0;
}