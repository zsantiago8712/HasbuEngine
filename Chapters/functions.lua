function programs(chapter_name, name)
    project(name)
    kind "WindowedApp"
    language "C++"
    cppdialect "C++20"
    toolset "gcc"

    includedirs {
        "../App",
        "../Dependencies",
    }

    links { 
        "App",
        "Glad:shared",
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


    files {  chapter_name .. "/%{prj.name}/**.cpp" }



    filter  "configurations:Debug"
        defines { "DEBUG" }
        targetdir("../../bin/Debug/" .. outputdir .. "/Programs/" .. chapter_name .. "/%{prj.name}")
        objdir("../../obj/Debug/" .. outputdir .. "/Programs/" .. chapter_name .. "/%{prj.name}")
        symbols "On"
      
      
    filter { "configurations:Release" }
        defines { "RELEASE" }
        targetdir("../../bin/Release/" .. outputdir .. "/Programs/" .. chapter_name .. "/%{prj.name}")
        objdir("../../obj/Release/" .. outputdir .. "/Programs/" .. chapter_name .. "/%{prj.name}")
        symbols "Off"
        optimize "Full"
end
