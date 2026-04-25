<<<<<<< HEAD
add_library(Request INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
=======
add_library(Request STATIC ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
>>>>>>> d5b11da3f4a2b250d4e3ad885d30ddec3eac211b

target_include_directories(Request INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)