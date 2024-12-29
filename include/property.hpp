// Utility/property.hpp

#pragma once

#include <functional>
#include <memory>
#include <variant>
#include <string_view>

#include "common.hpp"


namespace utl {

    tmp<tn T>
    class Property {
    private:
        using _get_func = std::function<T()>;
        using _set_func = std::function<void(T)>;
        using _get_set_variant = std::variant<std::monostate, _get_func, _set_func>;

    public:        
        struct Accessor {
            const std::string_view key;
            const _get_set_variant func;

            Accessor() : key("nil"), func(std::monostate{}) {}
            Accessor(const std::string_view& _key, _get_set_variant _func = std::monostate{}) : key(_key), func(_func) {}
        };

    public:
        Property(T& var) : m_getter([&var]() { return var; }), m_setter([&var](T value) { var = value; }) {}
        Property(T& var, const Accessor& first, const Accessor& second = Accessor())
            : m_getter(std::get<_get_func>(ProcessAccessors(first, second, "get", var))),
            m_setter(std::get<_set_func>(ProcessAccessors(first, second, "set", var))) {}

        operator T() const;

        Property<T>& operator=(Property<T>& other);
        Property<T>& operator=(T value);
        Property<T>& operator+=(T value);
        Property<T>& operator-=(T value);

        friend std::ostream& operator<<(std::ostream& os, const Property& property) {
            return os << property.m_getter();
        }
    
    private:
        const _get_func m_getter;
        const _set_func m_setter;

        _get_set_variant ProcessAccessors(const Accessor& first, const Accessor& second, const std::string_view& key, T& var);

    };

}


#include "property.inl"