target_sources(NauLib
    PRIVATE
        V8Manager.cpp
        util/FileService.cpp
        util/Logger.cpp
        GlobalMapper.cpp
    PUBLIC
        V8Manager.h
        util/FileService.h
        util/Logger.h
        GlobalMapper.h
)

target_include_directories(NauLib PUBLIC ${CMAKE_CURRENT_LIST_DIR})