// Utility/include/Maths/matrix.hpp

#pragma once

#include <array>

#include "Containers/interval_span.hpp"


namespace utl {

    tmp<std::size_t N, std::size_t Q>
    constexpr bool Is_Valide_Size = N >= 1 && Q >= 1;

    tmp<std::size_t N, std::size_t Q>
    concept Valide_Size = Is_Valide_Size<N, Q>;

    tmp<std::size_t N, std::size_t Q>
    constexpr bool Has_Exactly_N_Args = N == Q;

    tmp<std::size_t N, std::size_t Q>
    concept ExactlyNArgs = Has_Exactly_N_Args<N, Q>;

    tmp<tn T, std::size_t N, std::size_t Q>
    requires(Standard_Arithmetic_t<T> && Valide_Size<N, Q>)
    class Matrix {

        using ValuesType = T;
        static constexpr std::size_t RowsNumber = N;
        static constexpr std::size_t ColumnsNumber = Q;
        static constexpr std::size_t ValuesNumber = N * Q;

        static constexpr std::size_t RowsEndIndex = RowsNumber - 1;
        static constexpr std::size_t ColumnsEndIndex = ColumnsNumber - 1;

    public:

        #pragma region Ctors

        constexpr Matrix() = default;
        constexpr Matrix(const ValuesType& value);
        constexpr Matrix(const std::array<ValuesType, ValuesNumber> values) : m_values(values) {}
        constexpr Matrix(const ValuesType* start, const ValuesType* end);
        
        tmp<tn... Args>
        requires(ExactlyNArgs<N * Q, sizeof...(Args)> && (std::same_as<Args, T> && ...))
        constexpr Matrix(Args&&... args) : m_values(std::forward<Args>(args)...) {}
        tmp<tn... Args>
        requires(ExactlyNArgs<N * Q, sizeof...(Args)> && (std::same_as<Args, T> && ...))
        constexpr Matrix(Args&... args) : m_values(std::forward<Args>(args)...) {}

        tmp<tn... Args>
        requires(ExactlyNArgs<N, sizeof...(Args)> && (std::same_as<Args, std::array<T, Q>> && ...))
        constexpr Matrix(Args&&... args);
        tmp<tn... Args>
        requires(ExactlyNArgs<N, sizeof...(Args)> && (std::same_as<Args, std::array<T, Q>> && ...))
        constexpr Matrix(Args&... args);

        #pragma endregion

        #pragma region Operator

        constexpr IntervalSpan<ValuesType> operator[](const std::size_t& index);
        constexpr const IntervalSpan<ValuesType> operator[](const std::size_t& index) const;

        constexpr Matrix<T, N, Q> operator+(const Matrix<T, N, Q>& rhs) const;
        constexpr Matrix<T, N, Q> operator-(const Matrix<T, N, Q>& rhs) const;

        tmp<tn Ty, std::size_t Ny, std::size_t Qy>
        requires(Standard_Arithmetic_t<Ty> && Valide_Size<Ny, Qy> && Equal<Ny, Q>)
        constexpr Matrix<T, N, Qy> operator*(const Matrix<Ty, Ny, Qy>& rhs) const;

        tmp<tn Ty>
        requires(Standard_Arithmetic_t<Ty>)
        constexpr Matrix<T, N, Q> operator*(const Ty& scalar) const;

        tmp<tn Ty>
        requires(Standard_Arithmetic_t<Ty>)
        constexpr Matrix<T, N, Q> operator/(const Ty& scalar) const;

        #pragma endregion

        #pragma region MemberFunctions

        constexpr IntervalSpan<ValuesType> GetRow(const std::size_t& index);
        constexpr const IntervalSpan<ValuesType> GetRow(const std::size_t& index) const;

        constexpr IntervalSpan<ValuesType> GetColumn(const std::size_t& index);
        constexpr const IntervalSpan<ValuesType> GetColumn(const std::size_t& index) const;

        constexpr Matrix<T, Q, N> Transpose() const;

        #pragma endregion

    private:
        ValuesType m_values[ValuesNumber];

    public:

        static const Matrix<ValuesType, N, Q> Zero;
        static const Matrix<ValuesType, N, Q> One;

        static constexpr const bool IsMatrixRow();
        static constexpr const bool IsMatrixColumn();
        static constexpr const bool IsMatrixSquare();

        friend std::ostream& operator<<(std::ostream& os, const Matrix<T, N, Q>& m) {
            for (std::size_t i = 0; i < N; i++) {
                os << m[i] << '\n';
            }
            return os;
        }

    };

}


#include "matrix.inl"