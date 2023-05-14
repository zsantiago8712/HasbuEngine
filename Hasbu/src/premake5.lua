project "App"
    kind "SharedLib"
    language "C++"
    cppdialect "C++20"
    toolset "gcc"


    defines { "OpenGL" }

    links { 
        "Glad:shared",
        "fmt",
        "Metal.framework",
        "CoreFoundation.framework",
        "QuartzCore.framework",
        "IOSurface.framework",
        "Cocoa.framework",
        "IOKit.framework",
        "glfw"
    }

    pchsource "defines.cpp"
    pchheader "defines.hpp"

    includedirs { "./", "../vendor", "../vendor/LA/src" }
    files { "Render/**.cpp", "Shader/**.cpp", "core/**.cpp",  "Platform/Window/**.cpp", "Platform/OpenGL/**.cpp" }


    filter "configurations:Debug"
        defines {"DEBUG"}
        targetdir("../../bin/Debug/" .. outputdir .. "/libs/%{prj.name}")
        objdir("../../obj/Debug/" .. outputdir .. "/libs/%{prj.name}")
        symbols "On"

    filter {"configurations:Release"}
        defines {"RELEASE"}
        targetdir("../../bin/Release/" .. outputdir .. "/libs/%{prj.name}")
        objdir("../../obj/Release/" .. outputdir .. "/libs/%{prj.name}")
        symbols "Off"
        optimize "Full"
