set(SOURCES)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    list(APPEND SOURCES 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ProxyLinux.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/ProxyLinux.h)

elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    list(APPEND SOURCES 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ProxyWindows.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/ProxyWindows.h)
endif()

add_library(Proxy STATIC ${SOURCES})

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_include_directories(Proxy STATIC ${CMAKE_CURRENT_SOURCE_DIR}/include/ProxyLinux.h)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_include_directories(Proxy STATIC ${CMAKE_CURRENT_SOURCE_DIR}/include/ProxyWindows.h)
endif()

target_link_directories(Proxy PRIVATE Request)
