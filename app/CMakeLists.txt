add_library(AppInterceptor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

target_include_directories(AppInterceptor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(App src/App.cpp)

target_link_directories(AppInterceptor INTERFACE Proxy)
target_link_directories(AppInterceptor INTERFACE Request)

