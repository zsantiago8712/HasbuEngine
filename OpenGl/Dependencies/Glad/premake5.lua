project "Glad"
kind "SharedLib"
language "C++"
cppdialect "C++20"
toolset "gcc"

links {"Metal.framework", "CoreFoundation.framework", "QuartzCore.framework", "IOSurface.framework", "Cocoa.framework",
       "IOKit.framework"}

includedirs {"../../Dependencies/"}

files {"glad.c"}

filter "configurations:Debug"
defines {"DEBUG"}
targetdir("../../../bin/Debug/" .. outputdir .. "/libs/%{prj.name}")
objdir("../../../obj/Debug/" .. outputdir .. "/libs/%{prj.name}")
symbols "On"

filter {"configurations:Release"}
defines {"RELEASE"}
targetdir("../../../bin/Release/" .. outputdir .. "/libs/%{prj.name}")
objdir("../../../obj/Release/" .. outputdir .. "/libs/%{prj.name}")

symbols "Off"
optimize "Full"
