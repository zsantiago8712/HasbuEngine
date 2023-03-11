project "Window"
    kind "SharedLib"
    language "C++"
    cppdialect "C++20"
    toolset "gcc"

    includedirs { "/Users/randymarsh/Developer/OpenGL/OpenGL/Dependencies" }

    links { 
        "Metal.framework",
        "CoreFoundation.framework",
        "QuartzCore.framework",
        "IOSurface.framework",
        "Cocoa.framework",
        "IOKit.framework",
        "CoreVideo.framework",
        "glfw",
        "fmt"
    }

    defines {
        "_GLFW_COCOA",
        "GLFW_EXPOSE_NATIVE_COCOA",
    }


    files { "**.cpp" }
    buildoptions {
        "-fvisibility=hidden"
    }



    filter  "configurations:Debug"
        defines { "DEBUG" }
        targetdir("../../../bin/Debug/" .. outputdir .. "/libs/%{prj.name}")
        objdir("../../../obj/Debug/" .. outputdir .. "/libs/%{prj.name}")
        symbols "On"
      
      
    filter { "configurations:Release" }
        defines { "RELEASE" }
        targetdir("../../../bin/Release/" .. outputdir .. "/libs/%{prj.name}")
        objdir("../../../obj/Release/" .. outputdir .. "/libs/%{prj.name}")

        symbols "Off"
        optimize "Full"