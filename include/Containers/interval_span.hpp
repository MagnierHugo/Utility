// Utility/include/Containers/interval_span.hpp

#pragma once

#include <iostream>
#include <vector>

#include "common.hpp"


namespace utl {

    tmp<tn T>
    class IntervalSpan {
    public:
        constexpr IntervalSpan() = default;
        constexpr IntervalSpan(const T* start, const T* end) : m_start(start), m_end(end), m_step(1) {}
        constexpr IntervalSpan(const T* start, const T* end, const std::size_t& step) : m_start(start), m_end(end), m_step(step) {}

        constexpr std::size_t size() const;
        constexpr std::vector<T> to_vect() const;

        constexpr T& operator[](const std::size_t& index);
        constexpr T operator[](const std::size_t& index) const;

        friend std::ostream& operator<<(std::ostream& os, const IntervalSpan<T>& span) {
            for (std::size_t i = 0; i < span.size(); i++) {
                os << span[i] << ' ';
            }
            return os;
        }

    private:
        const T* m_start;
        const T* m_end;
        const std::size_t m_step;

    };

}

#include "interval_span.inl"