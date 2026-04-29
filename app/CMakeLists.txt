add_library(AppInterceptor STATIC ${CMAKE_CURRENT_SOURCE_DIR}/src/App.cpp)

target_include_directories(AppInterceptor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

include(FetchContent)
 
FetchContent_Declare(ftxui
    GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI
    GIT_TAG main
)
 
FetchContent_MakeAvailable(ftxui)

target_link_libraries(AppInterceptor PRIVATE Proxy Request ftxui::screen ftxui::dom ftxui::component)
