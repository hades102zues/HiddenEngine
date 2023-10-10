-- premake tokens 

workspace "Hidden"
    configurations {"Debug", "Release"}




-- Define a table to hold the third-party dependencies directories
externalDeps = {}
externalDeps["Glad"] = "third-party/glad"
externalDeps["Glm"] = "third-party/glm"
externalDeps["Sdl2"] = "third-party/mac_sdl2_core"
externalDeps["SpdLog"] = "third-party/spdlog"


--- **************************************
--- *** GENERATE EXTERNAL LIB FILES ***


-- include(): Control moves to the directory passed in the argument and executes the premake5.lua.
-- The include must NEVER be placed within the body of another project otherwise subsequent attributions
-- will instead be applied under the include's project domain

-- build glad 
include(externalDeps.Glad)




project "HiddenEngine"
    kind "ConsoleApp" -- set what the binary end product would be. in this case an executable
    location "build" -- The user defined location for all project files, unless specifically overrided to be elsewhere.
    language "C++"
    cppdialect "C++17"

    targetname "hidden" -- name of end product 
    targetdir "." -- location of the end product 

    flags { 
        -- Compiler flags
        "FatalWarnings" -- -Werrors
    }
    
    postbuildcommands {
      -- 
      --  ,"rm -f %{cfg.buildtarget.directory}/Makefile"
       -- "clear"
       "rm -rf %{cfg.buildtarget.directory}/build"
        ,"%{cfg.buildtarget.directory}/%{cfg.buildtarget.name}"
        
        
    }


--- **************************************
--- *** PROCESSOR INCLUDES ***
--- must be specified before files{}


    externalincludedirs {     -- Allows user to add paths to compiler’s system directory list, typically done via  -I or -isystem compiler flag. 
        "%{externalDeps.Glad}/include"
        ,"%{externalDeps.Glm}/include"
        ,"%{externalDeps.Sdl2}/include"
        ,"%{externalDeps.SpdLog}/include"
        
    }

--- **************************************
--- *** SOURCES and files ***

    files {
        "src/**.cpp"
        --,"src/engine-core/window/*.cpp"
    }

    defines {
        "GLFW_INCLUDE_NONE" -- Tell Glad to not include GLFW
    }


--- **************************************
--- *** LIBS ***

    libdirs {
        "%{externalDeps.Sdl2}/lib"
        ,"%{externalDeps.Glad}/build/lib"
    }

    links {
        "Cocoa.framework"
        ,"OpenGL.framework"
        ,"CoreVideo.framework"
        ,"IOKit.framework"
        ,"SDL2"
        ,"glad"
    }



    filter {"system:*", "configurations:Debug"}
        defines "HIDDEN_CONFIG_DEBUG"
        symbols "on" --debug info / -g
        runtime "Debug"
        
    filter {"system:*", "configurations:Release"}
        defines "HIDDEN_CONFIG_RELEASE"
        symbols "off" --debug info / -g
        runtime "Release"
        optimize "on"

    filter {"system:macosx", "configurations:*"}
        defines "HIDDEN_PLATFORM_MAC"
        systemversion "12.0" -- set lowest os compatibility

    filter {"system:windows", "configurations:*"}
        defines "HIDDEN_PLATFORM_WINDOWS"