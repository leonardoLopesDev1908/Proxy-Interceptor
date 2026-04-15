add_library(Request STATIC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

target_include_directories(Request STATIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
