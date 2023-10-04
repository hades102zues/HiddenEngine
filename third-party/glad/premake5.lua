
project "glad"
    kind "StaticLib"
    language "C"
    staticruntime "on"
    targetdir("build/lib")


    files {
        "include/**.h"
        ,"src/**.c"
    }

    includedirs {
        "include"
    }

    postbuildcommands {
          "rm -rf obj"    -- remove extra files generated
    }