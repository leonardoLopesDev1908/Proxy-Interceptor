add_library(ProxyWindows STATIC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

target_include_directories(ProxyWindows STATIC ${CMAKE_CURRENT_SOURCE_DIR}/include)