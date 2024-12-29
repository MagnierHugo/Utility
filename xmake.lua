-- Custom/xmake.lua

add_rules("mode.debug", "mode.release")

target("Utility")
    set_rundir(".")
    set_languages("c++20")
    add_files("src/**.cpp")
    add_headerfiles("include/**.hpp")
    add_includedirs("include")

    if is_mode("debug") then
        set_symbols("debug")
        set_optimize("none")
    end

    if is_mode("release") then
        set_symbols("hidden")
        set_optimize("fastest")
        set_strip("all")
    end