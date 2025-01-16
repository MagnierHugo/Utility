// Utility/include/Containers/interval_span.inl


namespace utl {

    tmp<tn T>
    constexpr std::size_t IntervalSpan<T>::size() const {
        return (m_end - m_start + m_step - 1) / m_step; // ceiling division
    }

    tmp<tn T>
    constexpr std::vector<T> IntervalSpan<T>::to_vect() const {
        T values[size()];
        for (std::size_t i = 0; i < size(); i++) {
            values[i] = *this[i];
        }
        return std::vector<T>(std::begin(values), std::end(values));
    }

    tmp<tn T>
    constexpr T& IntervalSpan<T>::operator[](const std::size_t& index) {
        if (index < size()) {
            return m_start[index * m_step];
        }

        std::cerr << "Error: The Index " << index << " is Out Of Range! (max was: " << size() << ")\n";
        throw std::out_of_range("Index Out of Range");
    }

    tmp<tn T>
    constexpr T IntervalSpan<T>::operator[](const std::size_t& index) const {
        if (index < size()) {
            return m_start[index * m_step];
        }

        std::cerr << "Error: The Index " << index << " is Out Of Range! (max was: " << size() << ")\n";
        throw std::out_of_range("Index Out of Range");
    }

}