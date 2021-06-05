cmake_minimum_required(VERSION 3.13.0)
project(NauLib VERSION 0.0.1)
add_executable(NauLib main.cpp)


#include js and other data files
include(CMakeRC.cmake)
cmrc_add_resource_library(js_scripts NAMESPACE "js" ${CMAKE_CURRENT_SOURCE_DIR}/scripts/main.ts)

# Download all the submodules
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Sumodule Update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT
        )
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

# Make sure dependencies exist
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/dependencies/bx/makefile")
    message(FATAL_ERROR "The bx submodule was not downloaded: GIT SUBMODULE was turned off or failed. Please update submodules and try again")
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/dependencies/bimg/makefile")
    message(FATAL_ERROR "The bimg submodule was not downloaded: GIT SUBMODULE was turned off or failed. Please update submodules and try again")
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/dependencies/bgfx/makefile")
    message(FATAL_ERROR "The bgfx submodule was not downloaded: GIT SUBMODULE was turned off or failed. Please update submodules and try again")
endif()

	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glfw)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

if(WIN32)
    #include dirs
    target_include_directories(NauLib 
        PRIVATE
            dependencies/bgfx/include
            dependencies/bx/include
            dependencies/bx/include/compat/msvc
            dependencies/bimg/include
            dependencies/glfw/include
            dependencies/v8/v8/include
            dependencies/v8/v8/include/libplatform
    )
    # add_library(glfw INTERFACE "${PROJECT_SOURCE_DIR}/dependencies/glfw/include/GLFW/glfw3.h")
    target_link_libraries(NauLib ${CMAKE_DL_LIBS} glfw bgfxDebug bimgDebug bxDebug v8_monolith dbghelp Winmm js_scripts)
	
    #BGFX LINKS LOGIC
    target_link_directories(NauLib PRIVATE dependencies/bgfx/.build/win64_vs2017/bin/)

    target_link_directories(NauLib PRIVATE C:/src/vcpkg/vcpkg/installed/x64-windows/lib/) #pthreads

    target_link_directories(NauLib PRIVATE dependencies/v8/v8/out/x64.debug/)
    target_link_directories(NauLib PRIVATE dependencies/v8/v8/out.gn/x64.debug/obj/)
    target_link_directories(NauLib PRIVATE dependencies/v8/v8/lib/)


    add_compile_definitions(V8_COMPRESS_POINTERS)
	if(MSVC)
		target_link_options(NauLib PUBLIC /NODEFAULTLIB:libcmtd.lib )
		target_compile_options(NauLib PUBLIC /MTd)
		target_compile_options(NauLib PUBLIC /D_ITERATOR_DEBUG_LEVEL=0)
	endif()

    if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
        if(NOT EXISTS "${PROJECT_SOURCE_DIR}/dependencies/bgfx/.build/win64_vs2017/bin/libbgfxDebug.a")
            message(FATAL_ERROR "The bgfx submodule was not built as debug! Go to bgfx folder and run: make vs2017-release64")
        endif()
        target_link_libraries(NauLib 
            bgfxDebug
            bimgDebug
            bxDebug
            example-glueDebug
            example-commonDebug
            bimg_decodeDebug
			
	    )
    elseif("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
        if(NOT EXISTS "${PROJECT_SOURCE_DIR}/dependencies/bgfx/.build/win64_vs2017/bin/bgfx-shared-libRelease.lib")
            message(FATAL_ERROR "The bgfx submodule was not built as release! Go to bgfx folder and run: make vs2017-release64")
        endif()
        target_link_libraries(NauLib
            bimg_decodeRelease
            bgfxRelease
            bimgRelease 
            bxRelease
        )
    endif()
endif()