// Utility/include/Maths/matrix.hpp

#pragma once

#include "common.hpp"


namespace utl {

    tmp<tn T>
    concept Standard_Arithmetic_t = Is_Standard_Arithmetic_t<T>;

    tmp<std::size_t N, std::size_t Q>
    constexpr bool Is_Valide_Size = N >= 1 && Q >= 1;

    tmp<std::size_t N, std::size_t Q>
    concept Valide_Size = Is_Valide_Size<N, Q>;

    tmp<Standard_Arithmetic_t T, std::size_t N, std::size_t Q>
    requires(Valide_Size<N, Q>)
    class Matrix {

        using ValuesType = T;
        static constexpr std::size_t RowsNumber = N;
        static constexpr std::size_t ColumnsNumber = Q;

        static constexpr std::size_t RowsEndIndex = RowsNumber - 1;
        static constexpr std::size_t ColumnsEndIndex = ColumnsNumber - 1;

    public:
        constexpr Matrix() = default;
        constexpr Matrix(const ValuesType values[RowsNumber][ColumnsNumber]) : m_values(values) {}
        constexpr Matrix(const ValuesType& value);
        constexpr Matrix(const ValuesType values[RowsNumber * ColumnsNumber]);

        constexpr ValuesType* operator[](const std::size_t& index); // The operator allows direct value modification
        constexpr Matrix<ValuesType, 1, Q> GetRow(const std::size_t& index);
        constexpr Matrix<ValuesType, N, 1> GetColumn(const std::size_t& index);

    private:
        ValuesType m_values[RowsNumber][ColumnsNumber];

    public:
    #if N == Q
        static constexpr Matrix<ValuesType, N, Q> Identity = []() -> Matrix<ValuesType, N, Q> {
            Matrix<T, N, Q> matrix{0};
            for (std::size_t i = 0; i < RowsNumber; i++) {
                matrix[i][i] = 1;
            }
            return matrix;
        }();

        static constexpr Matrix<ValuesType, Q, Q> RightIdentity = Identity;
    #else
        static constexpr Matrix<ValuesType, Q, Q> RightIdentity = []() -> Matrix<T, ColumnsNumber, ColumnsNumber> {
            Matrix<T, N, Q> matrix{0};
            for (std::size_t i = 0; i < ColumnsNumber; i++) {
                matrix[i][i] = 1;
            }
            return matrix;
        }();
    #endif

        static constexpr Matrix<ValuesType, N, N> LeftIndentity = []() -> Matrix<T, N, Q> {
            Matrix<T, N, Q> matrix{0};
            for (std::size_t i = 0; i < RowsNumber; i++) {
                matrix[i][i] = 1;
            }
            return matrix;
        }();

        static constexpr Matrix<ValuesType, N, Q> Zero{0};
        static constexpr Matrix<ValuesType, N, Q> One{1};

        static constexpr bool IsMatrixRow();
        static constexpr bool IsMatrixColumn();
        static constexpr bool IsMatrixSquare();

    };

}


#include "matrix.inl"