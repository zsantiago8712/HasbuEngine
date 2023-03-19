project "Sandbox"
    kind "WindowedApp"
    language "C++"
    cppdialect "C++20"
    toolset "gcc"

    links { 
        "App:shared",
        "fmt"
    }

    includedirs {
        "../Hasbu/src/",
    }



    files {  "src/**.cpp" }
    

    filter  "configurations:Debug"
        defines { "DEBUG" }
        targetdir("../bin/Debug/" .. outputdir .. "/%{prj.name}")
        objdir("../obj/Debug/" .. outputdir .. "/%{prj.name}")
        symbols "On"

    
    filter { "configurations:Release" }
        defines { "RELEASE" }
        targetdir("../bin/Release/" .. outputdir .. "%{prj.name}")
        objdir("../obj/Release/" .. outputdir .. "%{prj.name}")
        symbols "Off"
        optimize "Full"