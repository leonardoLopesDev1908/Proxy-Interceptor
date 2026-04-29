#include "ftxui/component/component.hpp"
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/table.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>

#include <iostream>
#include <stdlib.h>
#include <thread>

using namespace ftxui;

enum class Page {
    Manual,
    Endpoint,
    Messages,
    Options,
    Exit
};

class App 
{
public:    
    App();

    void start();
    ftxui::Element manual_page();
    ftxui::Element input_endpoint_page();
    ftxui::Element messages_menu_page();
    ftxui::Element options_page();

private:
    std::string host;
    std::string port;
    int selected = 0;
    Page current_page = Page::Manual;

    ftxui::Component menu;
    ftxui::Component inputHost = Input(&host, "Host");
    ftxui::Component inputPort = Input(&port, "Port");
    ftxui::Component input_container;
    ftxui::Component main_container;
};
