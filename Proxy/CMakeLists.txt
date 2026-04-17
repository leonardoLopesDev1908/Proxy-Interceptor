add_library(Proxy INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(proxylinux)
add_subdirectory(proxywindows)

target_include_directories(Proxy INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)