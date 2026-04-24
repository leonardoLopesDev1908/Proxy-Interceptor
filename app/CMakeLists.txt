add_library(AppInterceptor ${CMAKE_CURRENT_SOURCE_DIR}/src/App.cpp)

target_include_directories(AppInterceptor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

include(FetchContent)
 
FetchContent_Declare(ftxui
    GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI
    GIT_TAG main
)
 
FetchContent_MakeAvailable(ftxui)

target_link_libraries(AppInterceptor PRIVATE Proxy Request ftxui::screen ftxui::dom ftxui::component)

add_executable(App "src/App.cpp")

target_link_libraries(App PRIVATE
        AppInterceptor
        ftxui::screen
        ftxui::dom
        ftxui::component
)
