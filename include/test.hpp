// Utility/test.hpp

#pragma once

#include <string>
#include <iostream>

#include "property.hpp"


namespace utl {

    class TestClass {
    public:
        Property<u32> Internal{};
        Property<u32> External{&m_external};

        TestClass(u32 external) : m_external(external) {}

        void LogExternal() const {
            std::cout << "Private member m_external: " << m_external << '\n';
        }

        tmp<tn T>
        static void GetLog(const Property<T>& p, const std::string& name) {
            std::cout << name << " Get: " << p << '\n';
        }

        tmp<tn T>
        static void SetLog(Property<T>& p, const std::string& name) {
            p = 42;
            std::cout << name << " Set: " << p.default_get() << '\n';
        }

        tmp<tn T>
        static void GetSetLog(Property<T>& p, const std::string& name) {
            GetLog(p, name);
            SetLog(p, name);
        }

    private:
        u32 m_external;

    };

}