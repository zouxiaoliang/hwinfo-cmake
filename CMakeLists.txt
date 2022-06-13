cmake_minimum_required(VERSION 3.5)

project(hwinfo LANGUAGES C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_SYSTEM_NAME MATCHES "Linux")
    message(FATAL_ERROR "thirdparty_libhwinfo not support ${CMAKE_SYSTEM_NAME}")
endif()

function(hwinfoMain)

    set(SRC_DIR hwinfo)

    #aux_source_directory(${SRC_DIR} SRC)
    aux_source_directory(${SRC_DIR}/src/hd SRC)
    aux_source_directory(${SRC_DIR}/src/ids SRC)
    aux_source_directory(${SRC_DIR}/src/isdn SRC)
    aux_source_directory(${SRC_DIR}/src/smps SRC)

    add_library(thirdparty_libhwinfo_static ${SRC})

    #target_include_directories(thirdparty_libhwinfo SYSTEM PUBLIC ${SRC_DIR})
    target_include_directories(thirdparty_libhwinfo_static SYSTEM PUBLIC ${SRC_DIR}/src/hd)
    target_include_directories(thirdparty_libhwinfo_static SYSTEM PUBLIC ${SRC_DIR}/src/ids)
    target_include_directories(thirdparty_libhwinfo_static SYSTEM PUBLIC ${SRC_DIR}/src/isdn)
    target_include_directories(thirdparty_libhwinfo_static SYSTEM PUBLIC ${SRC_DIR}/src/smp)
    target_link_libraries(thirdparty_libhwinfo_static thirdparty_libx86emu thirdparty_uuid)

    add_library(thirdparty_libhwinfo INTERFACE)
    target_include_directories(thirdparty_libhwinfo INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
    target_link_libraries(thirdparty_libhwinfo PUBLIC INTERFACE thirdparty_libhwinfo_static)

    add_dependencies(thirdparty_libhwinfo thirdparty_libhwinfo_static)

endfunction()

function(hwinfoCliMain)
    set(SRC_DIR hwinfo)
    add_executable(hwinfo_cli ${SRC_DIR}/hwinfo.c)
    target_link_libraries(hwinfo_cli thirdparty_libhwinfo)
endfunction()

function(hwinfoEasyMain)
    set(MAIN_SOURCES easy/HardwareInfo.cpp)
    add_library(thirdparty_libhwinfo_easy ${MAIN_SOURCES})
    target_link_libraries(thirdparty_libhwinfo_easy thirdparty_libhwinfo)
    target_include_directories(thirdparty_libhwinfo_easy SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
endfunction(hwinfoEasyMain)

hwinfoMain()
hwinfoEasyMain()

hwinfoCliMain()
