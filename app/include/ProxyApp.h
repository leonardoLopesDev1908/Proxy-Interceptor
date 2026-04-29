#ifdef _WIN32
#include "ProxyWindows.h"
#elif __linux__
#include "ProxyLinux.h"
#endif

#include "ftxui/component/component.hpp"
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/table.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>

#include <future>
#include <iostream>
#include <queue>
#include <stdlib.h>
#include <thread>

using namespace ftxui;

class ProxyApp 
{
public:    
    void start();
    ftxui::Element manual_page();
    ftxui::Element input_endpoint_page();
    ftxui::Element messages_menu_page();
    ftxui::Element options_page();

private:

    struct MessagesMenuState
    {
        //std::queue<Message> messages;
        int selectedMessage = 0;
    };

    struct OptionsState
    {
        bool readOnlyFlag = true;
        enum class Language {English, Portuguese, Spanish};
    };

    struct InputEndpointState 
    {
        std::string host;
        std::string port;
    };

private:
    int selected = 0;
    int activeTab = 0;

    InputEndpointState endpointState;
    MessagesMenuState messagesMenu;
    OptionsState optionsState;

    ftxui::Component menu;
    ftxui::Component inputHost;
    ftxui::Component inputPort;

    ftxui::Component main_container;
    ftxui::Component input_container;
    ftxui::Component menu_container;
    ftxui::Component messages_container;
};
