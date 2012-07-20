local SFML_LIBRARIES = "-lsfml-graphics -lsfml-window -lsfml-system" 
local BOOST_LIBRARIES = "-lboost_system -lboost_filesystem -lboost_serialization"

solution "Danmaku"
    configurations { "Debug", "Release" }
    flags { "ExtraWarnings","FloatFast" }
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
        buildoptions { "-std=c++11" }
        linkoptions { SFML_LIBRARIES, BOOST_LIBRARIES }

    project "Danmaku"
        kind "WindowedApp"
        language "C++"        
        targetdir "build"
        files { "src/Danmaku/**.cpp" }    
        links { "BlackDragonEngine" } 
        buildoptions { "-std=c++11" }
        linkoptions { SFML_LIBRARIES, BOOST_LIBRARIES }
