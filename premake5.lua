workspace "Hasbu"
    configurations { "Debug", "Release" }
    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    include "Hasbu/vendor/Glad"
    include "Hasbu/src"
    -- include "Hasbu/Chapters"
    include "Sandbox"


newaction {
    trigger = "clean",
    description = "Clean all bin and obj files",
    execute = function()
        print("Removing binaries")
        os.rmdir("./bin")
        os.rmdir("./obj")
        os.rmdir("./bin-libs")
        os.rmdir("./obj-libs")
        os.remove("Makefile")
        os.remove("App/Makefile")
        os.remove("App/src/platform/Makefile")
    end
}