set(SOURCES)
set(PROXY_INCLUDE_DIR)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    list(APPEND SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/ProxyLinux.cpp)
    set(PROXY_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/linux)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    list(APPEND SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/ProxyWindows.cpp)
    set(PROXY_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/windows)
endif()

add_library(Proxy STATIC ${SOURCES})

target_include_directories(Proxy PUBLIC ${PROXY_INCLUDE_DIR})

target_link_directories(Proxy PRIVATE Message)
