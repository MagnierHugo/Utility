// Utility/include/Maths/matrix.inl

#pragma once

#include <iostream>
#include <stdexcept>
#include <format>


namespace utl {

    tmp<Standard_Arithmetic_t T, std::size_t N, std::size_t Q>
    requires(Valide_Size<N, Q>)
    constexpr bool Matrix<T, N, Q>::IsMatrixRow() {
        return RowsNumber == 1;
    }

    tmp<Standard_Arithmetic_t T, std::size_t N, std::size_t Q>
    requires(Valide_Size<N, Q>)
    constexpr bool Matrix<T, N, Q>::IsMatrixColumn() {
        return ColumnsNumber == 1;
    }

    tmp<Standard_Arithmetic_t T, std::size_t N, std::size_t Q>
    requires(Valide_Size<N, Q>)
    constexpr bool Matrix<T, N, Q>::IsMatrixSquare() {
        return ColumnsNumber == RowsNumber;
    }


    tmp<Standard_Arithmetic_t T, std::size_t N, std::size_t Q>
    requires(Valide_Size<N, Q>)
    constexpr Matrix<T, N, Q>::Matrix(const T& value) {
        if constexpr (N == 1) {
            for (std::size_t i = 0; i < ColumnsNumber; i++) {
                m_values[0][i] = value;
            }
        } else if constexpr (Q == 1) {
            for (std::size_t i = 0; i < RowsNumber; i++) {
                m_values[i][0] = value;
            }
        } else {
            for (std::size_t i = 0; i < RowsNumber; i++) {
                for (std::size_t j = 0; j < ColumnsNumber; j++) {
                    m_values[i][j] = value;
                }
            }
        }
    }

    tmp<Standard_Arithmetic_t T, std::size_t N, std::size_t Q>
    requires(Valide_Size<N, Q>)
    constexpr Matrix<T, N, Q>::Matrix(const T values[RowsNumber * ColumnsNumber]) {
        if constexpr (IsMatrixRow()) {
            m_values[0] = values;
        } else if constexpr (IsMatrixColumn()) {
            for (std::size_t i = 0; i < RowsNumber; i++) {
                m_values[i][0] = values[i];
            }
        } else {
            for (std::size_t i = 0; i < RowsNumber; i++) {
                for (std::size_t j = 0; j < ColumnsNumber; j++) {
                    m_values[i][j] = values[i == 0 ? i + j : i * j];
                }
            }
        }
    }

    tmp<Standard_Arithmetic_t T, std::size_t N, std::size_t Q>
    requires(Valide_Size<N, Q>)
    constexpr T* Matrix<T, N, Q>::operator[](const std::size_t& index) {
        if (index > RowsEndIndex) {
            std::cerr << std::format("Invalide Index: {} is Out Of Range (max is: {})", index, RowsEndIndex);
            throw std::out_of_range("Index Out of Range");
        }
        return m_values[index];
    }

    tmp<Standard_Arithmetic_t T, std::size_t N, std::size_t Q>
    requires(Valide_Size<N, Q>)
    constexpr Matrix<T, 1, Q> Matrix<T, N, Q>::GetRow(const std::size_t& index) {
        if (index > RowsEndIndex) {
            std::cerr << std::format("Invalide Index: {} is Out Of Range (max is: {})", index, RowsEndIndex);
            throw std::out_of_range("Index Out of Range");
        }
        return Matrix<T, 1, Q>(m_values[index]);
    }

    tmp<Standard_Arithmetic_t T, std::size_t N, std::size_t Q>
    requires(Valide_Size<N, Q>)
    constexpr Matrix<T, N, 1> Matrix<T, N, Q>::GetColumn(const std::size_t& index) {
        if (index > ColumnsEndIndex) {
            std::cerr << std::format("Invalide Index: {} is Out Of Range (max is: {})", index, ColumnsEndIndex);
            throw std::out_of_range("Index Out of Range");
        }
        T column[N];
        for (std::size_t i = 0; i < N; i++) {
            column[i] = m_values[i][index];
        }
        return Matrix<T, N, 1>(column);
    }

}