// Utility/property.inl

#pragma once

#include <cassert>


namespace utl {

    tmp<tn T>
    Property<T>::operator T() const {
        return m_getter();
    }
    
    tmp<tn T>
    Property<T>& Property<T>::operator=(Property<T>& other) {
        m_setter(other);
        return *this;
    }

    tmp<tn T>
    Property<T>& Property<T>::operator=(T value) {
        m_setter(value);
        return *this;
    }

    tmp<tn T>
    Property<T>& Property<T>::operator+=(T value) {
        m_setter(m_getter() + value);
        return *this;
    }

    tmp<tn T>
    Property<T>& Property<T>::operator-=(T value) {
        m_setter(m_getter() - value);
        return *this;
    }

    tmp<tn T>
    Property<T>::_get_set_variant Property<T>::ProcessAccessors(const Accessor& first, const Accessor& second, const std::string_view& key, T& var) {
        if (first.key == key) {
            if (!std::holds_alternative<std::monostate>(first.func)) {
                return first.func;
            }

            if (key == "get") {
                return [&var]() { return var; };
            }

            return [&var](T value) { var = value; };
        }
        
        if (second.key == key) {
            if (!std::holds_alternative<std::monostate>(second.func)) {
                return second.func;
            }

            if (key == "get") {
                return [&var]() { return var; };
            }

            return [&var](T value) { var = value; };
        }

        if (key == "get") {
            return []() {
                assert(false && "This property is Write Only and thus doesn't have a getter !!");
                return T();
            };
        }

        return [](T value) { assert(false && "This property is Read Only and thus doesn't have a setter !!"); };
    }

}