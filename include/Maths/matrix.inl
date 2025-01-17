// Utility/include/Maths/matrix.inl

#pragma once


namespace utl {

    #pragma region StaticMembers

    tmp<tn T, std::size_t N, std::size_t Q>
    requires(Standard_Arithmetic_t<T> && Valide_Size<N, Q>)
    const Matrix<T, N, Q> Matrix<T, N, Q>::Zero{0};

    tmp<tn T, std::size_t N, std::size_t Q>
    requires(Standard_Arithmetic_t<T> && Valide_Size<N, Q>)
    const Matrix<T, N, Q> Matrix<T, N, Q>::One{1};

    tmp<tn T, std::size_t N, std::size_t Q>
    requires(Standard_Arithmetic_t<T> && Valide_Size<N, Q>)
    constexpr const bool Matrix<T, N, Q>::IsMatrixRow() {
        return N == 1;
    }

    tmp<tn T, std::size_t N, std::size_t Q>
    requires(Standard_Arithmetic_t<T> && Valide_Size<N, Q>)
    constexpr const bool Matrix<T, N, Q>::IsMatrixColumn() {
        return Q == 1;
    }

    tmp<tn T, std::size_t N, std::size_t Q>
    requires(Standard_Arithmetic_t<T> && Valide_Size<N, Q>)
    constexpr const bool Matrix<T, N, Q>::IsMatrixSquare() {
        return N == Q;
    }

    #pragma endregion


    #pragma region Ctors

    tmp<tn T, std::size_t N, std::size_t Q>
    requires(Standard_Arithmetic_t<T> && Valide_Size<N, Q>)
    constexpr Matrix<T, N, Q>::Matrix(const ValuesType& value) {
        for (std::size_t i = 0; i < ValuesNumber; i++) {
            m_values[i] = value;
        }
    }

    tmp<tn T, std::size_t N, std::size_t Q>
    requires(Standard_Arithmetic_t<T> && Valide_Size<N, Q>)
    constexpr Matrix<T, N, Q>::Matrix(const T* start, const T* end) {
        std::copy(start, end, m_values);
    }

    tmp<tn T, std::size_t N, std::size_t Q>
    requires(Standard_Arithmetic_t<T> && Valide_Size<N, Q>)
    tmp<tn... Args>
    requires(ExactlyNArgs<N, sizeof...(Args)> && (std::same_as<Args, std::array<T, Q>> && ...))
    constexpr Matrix<T, N, Q>::Matrix(Args&&... args) {
        std::size_t index = 0;
        _ = std::initializer_list<T>{
            (
                std::copy(std::forward<Args>(args).begin(), std::forward<Args>(args).end(), m_values + index),
                index += Q, 0
            )...
        };
    }

    tmp<tn T, std::size_t N, std::size_t Q>
    requires(Standard_Arithmetic_t<T> && Valide_Size<N, Q>)
    tmp<tn... Args>
    requires(ExactlyNArgs<N, sizeof...(Args)> && (std::same_as<Args, std::array<T, Q>> && ...))
    constexpr Matrix<T, N, Q>::Matrix(Args&... args) {
        std::size_t index = 0;
        _ = std::initializer_list<T>{
            (
                std::copy(std::forward<Args>(args).begin(), std::forward<Args>(args).end(), m_values + index),
                index += Q, 0
            )...
        };
    }

    #pragma endregion

    #pragma region Operators

    tmp<tn T, std::size_t N, std::size_t Q>
    requires(Standard_Arithmetic_t<T> && Valide_Size<N, Q>)
    constexpr IntervalSpan<T> Matrix<T, N, Q>::operator[](const std::size_t& index) {
        if (index < RowsNumber) {
            const std::size_t start_index = index * ColumnsNumber;
            return IntervalSpan<T>(&m_values[start_index], &m_values[start_index + ColumnsNumber]);
        }

        std::cerr << "Error: The Index " << index << " is Out Of Range! (max was: " << RowsEndIndex << ")\n";
        throw std::out_of_range("Index Out of Range");
    }

    tmp<tn T, std::size_t N, std::size_t Q>
    requires(Standard_Arithmetic_t<T> && Valide_Size<N, Q>)
    constexpr const IntervalSpan<T> Matrix<T, N, Q>::operator[](const std::size_t& index) const {
        if (index < RowsNumber) {
            const std::size_t start_index = index * ColumnsNumber;
            return IntervalSpan<T>(&m_values[start_index], &m_values[start_index + ColumnsNumber]);
        }

        std::cerr << "Error: The Index " << index << " is Out Of Range! (max was: " << RowsEndIndex << ")\n";
        throw std::out_of_range("Index Out of Range");
    }

    tmp<tn T, std::size_t N, std::size_t Q>
    requires(Standard_Arithmetic_t<T> && Valide_Size<N, Q>)
    tmp<tn Ty, std::size_t Ny, std::size_t Qy>
    requires(Standard_Arithmetic_t<Ty> && Valide_Size<Ny, Qy> && Equal<Ny, Q>)
    constexpr Matrix<T, N, Qy> Matrix<T, N, Q>::operator*(const Matrix<Ty, Ny, Qy>& rhs) const {
        // T values[N * Qy];
        Matrix<T, N, Qy> m{0};
        for (std::size_t i = 0; i < N; i++) {
            const auto lhs_row = GetRow(i);
            for (std::size_t j = 0; j < Qy; j++) {
                const auto rhs_column = rhs.GetColumn(j);
                for (std::size_t k = 0; k < Q; k++) {
                    // values[i * Qy + j] += lhs_row[k] * rhs_column[k];
                    m.m_values[i * Qy + j] += lhs_row[k] * rhs_column[k];
                }
            }
        }
        return m;
    }

    tmp<tn T, std::size_t N, std::size_t Q>
    requires(Standard_Arithmetic_t<T> && Valide_Size<N, Q>)
    tmp<tn Ty>
    requires(Standard_Arithmetic_t<Ty>)
    constexpr Matrix<T, N, Q> Matrix<T, N, Q>::operator*(const Ty& scalar) const {
        Matrix<T, N, Q> m;
        for (std::size_t i = 0; i < ValuesNumber; i++) {
            m.m_values[i] = m_values * scalar;
        }
        return m;
    }

    tmp<tn T, std::size_t N, std::size_t Q>
    requires(Standard_Arithmetic_t<T> && Valide_Size<N, Q>)
    tmp<tn Ty>
    requires(Standard_Arithmetic_t<Ty>)
    constexpr Matrix<T, N, Q> Matrix<T, N, Q>::operator/(const Ty& scalar) const {
        Matrix<T, N, Q> m;
        for (std::size_t i = 0; i < ValuesNumber; i++) {
            m.m_values[i] = m_values / scalar;
        }
        return m;
    }

    #pragma endregion

    #pragma region MemberFunctions

    tmp<tn T, std::size_t N, std::size_t Q>
    requires(Standard_Arithmetic_t<T> && Valide_Size<N, Q>)
    constexpr IntervalSpan<T> Matrix<T, N, Q>::GetRow(const std::size_t& index) {
        if (index < RowsNumber) {
            const std::size_t start_index = index * ColumnsNumber;
            return IntervalSpan<T>(&m_values[start_index], &m_values[start_index + ColumnsNumber]);
        }

        std::cerr << "Error: The Index " << index << " is Out Of Range! (max was: " << RowsEndIndex << ")\n";
        throw std::out_of_range("Index Out of Range");
    }

    tmp<tn T, std::size_t N, std::size_t Q>
    requires(Standard_Arithmetic_t<T> && Valide_Size<N, Q>)
    constexpr const IntervalSpan<T> Matrix<T, N, Q>::GetRow(const std::size_t& index) const {
        if (index < RowsNumber) {
            const std::size_t start_index = index * ColumnsNumber;
            return IntervalSpan<T>(&m_values[start_index], &m_values[start_index + ColumnsNumber]);
        }

        std::cerr << "Error: The Index " << index << " is Out Of Range! (max was: " << RowsEndIndex << ")\n";
        throw std::out_of_range("Index Out of Range");
    }

    tmp<tn T, std::size_t N, std::size_t Q>
    requires(Standard_Arithmetic_t<T> && Valide_Size<N, Q>)
    constexpr IntervalSpan<T> Matrix<T, N, Q>::GetColumn(const std::size_t& index) {
        if (index < ColumnsNumber) {
            return IntervalSpan<T>(&m_values[index], &m_values[(RowsEndIndex * ColumnsNumber) + (index + 1)], ColumnsNumber);
        }

        std::cerr << "Error: The Index " << index << " is Out Of Range! (max was: " << ColumnsEndIndex << ")\n";
        throw std::out_of_range("Index Out of Range");
    }

    tmp<tn T, std::size_t N, std::size_t Q>
    requires(Standard_Arithmetic_t<T> && Valide_Size<N, Q>)
    constexpr const IntervalSpan<T> Matrix<T, N, Q>::GetColumn(const std::size_t& index) const {
        if (index < ColumnsNumber) {
            return IntervalSpan<T>(&m_values[index], &m_values[(RowsEndIndex * ColumnsNumber) + (index + 1)], ColumnsNumber);
        }

        std::cerr << "Error: The Index " << index << " is Out Of Range! (max was: " << ColumnsEndIndex << ")\n";
        throw std::out_of_range("Index Out of Range");
    }

    tmp<tn T, std::size_t N, std::size_t Q>
    requires(Standard_Arithmetic_t<T> && Valide_Size<N, Q>)
    constexpr Matrix<T, Q, N> Matrix<T, N, Q>::Transpose() const {
        
    }

    #pragma endregion

}