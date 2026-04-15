add_library(ProxyLinux STATIC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

target_include_directories(ProxyLinux STATIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_directories(ProxyLinux PRIVATE Request)
