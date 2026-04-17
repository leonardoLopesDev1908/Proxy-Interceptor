add_library(Request STATIC ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

target_include_directories(Request INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)