// Utility/property.hpp

#pragma once

#include <functional>
#include <optional>
#include <variant>
#include <string_view>

#include "common.hpp"


namespace utl {

    tmp<tn T>
    class Property {
    private:
        using _get_func = std::optional<std::function<T()>>;
        using _set_func = std::optional<std::function<void(const T&)>>;
        using _get_set_variant = std::variant<std::monostate, std::function<T()>, std::function<void(const T&)>>;

        friend class TestClass;

        struct Accessor {
            const std::string_view key;
            const _get_set_variant func;
            Accessor() : key("null"), func(std::monostate{}) {}
            Accessor(const std::string_view& _key, const _get_set_variant& _func = std::monostate{});
        };

        struct Accessors {
            Accessor get;
            Accessor set;
            Accessors(const Accessor& first, const Accessor& second = Accessor());
        };
        
        std::function<T()> default_get{
            [this]() -> T { 
                // return std::visit([this](auto&& arg) -> T {
                //     if constexpr (std::is_same_v<std::decay_t<decltype(arg)>, T>) {
                //         return arg; // Directly return the value if it matches T
                //     } else if constexpr (std::is_pointer_v<std::decay_t<decltype(arg)>>) {
                //         return *arg; // Dereference if it's a pointer
                //     } else {
                //         static_assert(always_false<decltype(arg)>::value, "Unsupported type in variant.");
                //     }
                // }, m_value); 
                if (auto result = std::get_if<std::shared_ptr<T>>(&m_value)) {
                    return **result;
                }
                return std::get<T>(m_value);
            }
        };

        std::function<void(const T&)> default_set{
            [this](const T& value) -> void {
                // std::visit([&value, this](auto&& arg) -> void {
                //     if constexpr (std::is_same_v<std::decay_t<decltype(arg)>, T>) {
                //         arg = value; // Directly assign if it's a value
                //     } else if constexpr (std::is_pointer_v<std::decay_t<decltype(arg)>>) {
                //         *arg = value; // Dereference if it's a pointer
                //     } else {
                //         static_assert(always_false<decltype(arg)>::value, "Unsupported type in variant.");
                //     }
                // }, m_value);
                if (auto result = std::get_if<std::shared_ptr<T>>(&m_value)) {
                    **result = value;
                } else {
                    m_value = value;
                }
            }
        };

    public:
        Property()
            : m_value(T()), m_getter(default_get), m_setter(default_set),
            m_is_external(false), m_has_getter(true), m_has_setter(true) {}
        Property(const Accessors& acc)
            : m_value(T()), m_getter(process_get(acc.get)), m_setter(process_set(acc.set)),
            m_is_external(false), m_has_getter(has_getter()), m_has_setter(has_setter()) {}

        Property(const T& value)
            : m_value(value), m_getter(default_get), m_setter(default_set),
            m_is_external(false), m_has_getter(true), m_has_setter(true) {}
        Property(const T& value, const Accessors& acc)
            : m_value(value), m_getter(process_get(acc.get)), m_setter(process_set(acc.set)),
            m_is_external(false), m_has_getter(has_getter()), m_has_setter(has_setter()) {}

        Property(const T* const value)
            : m_value(std::make_shared<T>(*value)), m_getter(default_get), m_setter(default_set),
            m_is_external(true), m_has_getter(true), m_has_setter(true) {}
        Property(const T* const value, const Accessors& acc)
            : m_value(std::make_shared<T>(*value)), m_getter(process_get(acc.get)), m_setter(process_set(acc.set)),
            m_is_external(true), m_has_getter(has_getter()), m_has_setter(has_setter()) {}

        operator T() const;

        Property& operator=(const T& value);
        Property& operator+=(const T& value);
        Property& operator-=(const T& value);
        Property& operator*=(const T& value);
        Property& operator/=(const T& value);

    private:
        // T& m_value;
        std::variant<T, std::shared_ptr<T>> m_value;
        const _get_func m_getter;
        const _set_func m_setter;

        const bool m_is_external, m_has_getter, m_has_setter;
        
        // union {
        //     T m_value;
        //     T& m_value_ref;
        // };

        // T default_get();
        // void default_set(const T& value);

        bool has_getter() const;
        bool has_setter() const;

        static _get_func process_get(const Accessor& get);
        static _set_func process_set(const Accessor& set);

    };

}


#include "property.inl"