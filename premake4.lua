local SFML_LIBRARIES = "-lsfml-graphics -lsfml-window -lsfml-system" 

solution "Danmaku"
    configurations { "Debug", "Release" }
    flags { "ExtraWarnings", "FatalWarnings", "FloatFast" }
    includedirs { "src/Headers" } 

    configuration "Debug"
        defines { "DEBUG" }
        flags { "Symbols" }

    configuration "Release"
        defines { "NDEBUG" }
        flags { "Optimize" }

    project "BlackDragonEngine"
        kind "StaticLib"
        language "C++"
        targetdir "lib"
        files { "src/BlackDragonEngine/**.cpp" }
        buildoptions { "-std=c++0x" }
        linkoptions { SFML_LIBRARIES }

    project "Danmaku"
        kind "WindowedApp"
        language "C++"        
        targetdir "build"
        files { "src/Danmaku/**.cpp" }    
        links { "BlackDragonEngine" } 
        buildoptions { "-std=c++0x" }
        linkoptions { SFML_LIBRARIES }
