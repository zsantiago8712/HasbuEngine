project "App"
kind "StaticLib"
language "C++"
cppdialect "C++20"
toolset "gcc"

includedirs {"../../OpenGL/App", "../Dependencies"}

links {"Glad:shared", "Window:shared"}

files {"core/**.cpp", "Shader/**.cpp"}

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
