// Utility/property.inl

#pragma once

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)


namespace utl {

    tmp<tn T>
    Property<T>::Accessor::Accessor(const std::string_view& _key, const _get_set_variant& _func) : key(_key), func(_func) {
        static_assert(
            _key == "get" || _key == "set",
            "Error: A Bad Accessor Qualifier was given !! (was: " TOSTRING(_key) ")\nError in file " TOSTRING(__FILE__) " at line " TOSTRING(__LINE__)
        );
    }

    tmp<tn T>
    Property<T>::Accessors::Accessors(const Accessor& first, const Accessor& second) {
        if (first.key == "get") {
            get = first;
            set = second;
            return;
        }

        get = second;
        set = first;
    }

    tmp<tn T>
    Property<T>::operator T() const {
        // static_assert(
        //     m_getter.has_value(), 
        //     "Error: This Property is WriteOnly and thus doesn't have a getter !!\nError in file " TOSTRING(__FILE__) " at line " TOSTRING(__LINE__)
        // );
        if (!m_getter.has_value()) {
            throw std::logic_error("Error: This Property is WriteOnly and thus doesn't have a getter !!\nError in file " TOSTRING(__FILE__) " at line " TOSTRING(__LINE__));
        } else {
            return (m_getter.value())();
        }
    }

    tmp<tn T>
    Property<T>& Property<T>::operator=(const T& value) {
        // static_assert(
        //     m_setter.has_value(), 
        //     "Error: This Property is ReadOnly and thus doesn't have a setter !!\nError in file " TOSTRING(__FILE__) " at line " TOSTRING(__LINE__)
        // );
        if (!m_getter.has_value()) {
            throw std::logic_error("Error: This Property is ReadOnly and thus doesn't have a setter !!\nError in file " TOSTRING(__FILE__) " at line " TOSTRING(__LINE__));
        } else {
            (m_setter.value())(value);
            return *this;
        }
    }

    tmp<tn T>
    Property<T>& Property<T>::operator+=(const T& value) {
        *this = default_get() + value;
        return *this;
    }

    tmp<tn T>
    Property<T>& Property<T>::operator-=(const T& value) {
        *this = default_get() - value;
        return *this;
    }

    tmp<tn T>
    Property<T>& Property<T>::operator*=(const T& value) {
        *this = default_get() * value;
        return *this;
    }

    tmp<tn T>
    Property<T>& Property<T>::operator/=(const T& value) {
        *this = default_get() / value;
        return *this;
    }

    // tmp<tn T>
    // T Property<T>::default_get() {
    //     std::visit([](auto&& arg) {
    //         if constexpr (is_external) {
    //             return *arg;
    //         } else {
    //             return arg;
    //         }
    //     });
    //     // return m_value;
    // }

    // tmp<tn T>
    // void Property<T>::default_set(const T& value) {
    //     std::visit([](auto&& arg) {
    //         if constexpr (is_external) {
    //             *arg = value;
    //         } else {
    //             arg = value;
    //         }
    //     });
    //     // m_value = value;
    // }

    tmp<tn T>
    bool Property<T>::has_getter() const {
        return m_getter.has_value();
    }

    tmp<tn T>
    bool Property<T>::has_setter() const {
        return m_setter.has_value();
    }
    
    tmp<tn T>
    Property<T>::_get_func Property<T>::process_get(const Accessor& get) {
        if (get.key == "null") { return std::nullopt_t{}; }
        if (const _get_func* result = std::get_if<_get_func>(&get.func)) { return *result; }
        return default_get;
    }

    tmp<tn T>
    Property<T>::_set_func Property<T>::process_set(const Accessor& set) {
        if (set.key == "null") { return std::nullopt_t{}; }
        if (const _set_func* result = std::get_if<_set_func>(&set.func)) { return *result; }
        return default_set;
    }

}