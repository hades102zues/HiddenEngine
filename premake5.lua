-- premake tokens 

workspace "Hidden"
    configurations {"Debug", "Release"}
    
    
project "HiddenEngine"
    location "build"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetname "hidengine"
    targetdir "."
    
    postbuildcommands {
        -- premake token are resolved based on the makefile they are called in. 
        -- these tokens will resolve in the makefile within the build folder
        -- relative to the build/Makefile where is the target's directory

        "rm -rf %{cfg.buildtarget.directory}/build"
        --,"rm -f %{cfg.buildtarget.directory}/Makefile"
        ,"%{cfg.buildtarget.directory}/%{cfg.buildtarget.name}"
    }

    files {
        "src/*.cpp"
        ,"third-party/glad/glad.c"
        ,"src/engine-core/game-engine/*.cpp"
        ,"src/renderer/render-manager/*.cpp"

    }

    includedirs {
        "third-party/glad/include"
        ,"third-party/glm/include"
        ,"third-party/sdl2_core/include"
    }

    libdirs {
        "third-party/sdl2_core/lib"
    }

    links {
        "Cocoa.framework"
        ,"OpenGL.framework"
        ,"CoreVideo.framework"
        ,"IOKit.framework"
        ,"SDL2"
    }