project "imgui_markup"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/obj/" .. outputdir .. "/%{prj.name}")

    pchheader "impch.h"
    pchsource "src/impch.cpp"

    files
    {
        "src/**.h",
        "src/**.cpp",
        "include/**.h"
    }

    includedirs
    {
        "src",
        "include",
        "%{include_dir.imgui}"
    }

    links
    {
        "imgui"
    }

    filter "system:windows"
        systemversion "latest"

    filter "system:linux"
        systemversion "latest"

    filter "configurations:Debug"
        symbols "on"
        defines "_DEBUG"

    filter "configurations:Release"
        optimize "on"
        defines "_RELEASE"
