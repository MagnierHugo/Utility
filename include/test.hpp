// Utility/test.hpp

#pragma once

#include <string>
#include <iostream>

#include "property.hpp"


namespace utl {

    class TestClass {
    private:
        tmp<tn T>
        using Accessor = Property<T>::Accessor;

    public:
        Property<i32> Default{m_var};

        Property<std::string> ReadOnlyBasic{
            m_var2,
           Accessor<std::string>("get")
        };
        Property<u32> ReadOnlyCustom{
            m_var4,
            Accessor<u32>("get", [this]() { std::cout << "Read Only Custom "; return m_var4; })
        };

        Property<b8> WriteOnlyBasic{
            m_var3,
            Accessor<b8>("set")
        };
        Property<float> WriteOnlyCustom{
            m_var5,
            Accessor<float>("set", [this](float value) { std::cout << "Write Custom Read Default\n"; m_var5 = value; })
        };

        Property<u32> ReadCustomWriteDefault{
            m_var6,
            Accessor<u32>("get", [this]() { std::cout << "Read Custom Write Default "; return m_var6; }),
            Accessor<u32>("set")
        };
        Property<u32> WriteCustomReadDefault{
            m_var7,
            Accessor<u32>("set", [this](u32 value) { std::cout << "Write Custom Read Default "; m_var7 = value; }),
            Accessor<u32>("get")
        };

        Property<double> FullCustom{
            m_var8,
            Accessor<double>("set", [this](double value) { std::cout << "Full Custom "; m_var8 = value; }),
            Accessor<double>("get", [this]() { std::cout << "Full Custom "; return m_var8; })
        };

        TestClass(i32 var, std::string var2, b8 var3, u32 var4, float var5, u32 var6, u32 var7, double var8)
            : m_var(var), m_var2(var2), m_var3(var3), m_var4(var4), m_var5(var5), m_var6(var6), m_var7(var7), m_var8(var8) {}

    private:
        i32 m_var;
        std::string m_var2;
        b8 m_var3;
        u32 m_var4;
        float m_var5;
        u32 m_var6;
        u32 m_var7;
        double m_var8;

    };

}