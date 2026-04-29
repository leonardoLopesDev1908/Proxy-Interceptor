#include "ProxyApp.h"

using namespace ftxui;

ftxui::Element ProxyApp::manual_page()
{
    return
        vbox({
            filler(),
            paragraph(R"(
            This program intends to be a simple way to check and edit HTTP messages, whether 
            its a request or a response. The idea to build this project came to me when i 
            started to study network programming in C++ and i saw how cool were some of BurpSuit 
            features.So i decided to make one on my own (maybe this part wasnt as cool as i thought).

            To be more straightforward, the flow is as follows :
                - After press "1" a input window will open waiting for you to enter a
                  endpoint(host + port) where this program will be listen for messages.
                  Example of input :
                        - host: 127.0.0.1
                        - port : 3000
                - Then, you will see a window where you can check a queue of all the messages that will
                  be arriving.You decide which message more attracts you(or if you are already looking
                  for some specific one, just wait for it) and what to do with it : change the method,
                  change content, and so on.
                - After chose a message, do all the operations you want to, you can just forward
                  the message to the server and, if you intend to, wait for the respective response.
                - If you are just watching for the messages and dont want to edit nothing(keep in
                  mind that the process of editing delays the messages sending until you make the
                  forwarding) you can disable the "Keep" flag, which means that the program will
                  just take the messages, make a register of it and automatically forward.)") | center | flex,
            filler(),
            }) | center | flex;
}

ftxui::Element ProxyApp::input_endpoint_page()
{
      return vbox({
        text("Endpoint Configuration") | bold,
        separator(),
        hbox({
            text("Host: "),
            inputHost->Render()
        }),

        hbox({
            text("Port: "),
            inputPort->Render()
        }),
        separator(),
        text("Esc to comeback to menu") | color(Color::GrayLight) | italic,
    }) | border;
}

ftxui::Element ProxyApp::messages_menu_page()
{
    auto table = Table({
        {"Version", "Marketing name", "Release date", "API level", "Runtime"},
        {"2.3", "Gingerbread", "February 9 2011", "10", "Dalvik 1.4.0"},
        {"4.0", "Ice Cream Sandwich", "October 19 2011", "15", "Dalvik"},
        {"4.1", "Jelly Bean", "July 9 2012", "16", "Dalvik"},
        {"4.2", "Jelly Bean", "November 13 2012", "17", "Dalvik"},
        {"4.3", "Jelly Bean", "July 24 2013", "18", "Dalvik"},
        {"4.4", "KitKat", "October 31 2013", "19", "Dalvik and ART"},
        {"5.0", "Lollipop", "November 3 2014", "21", "ART"},
        {"5.1", "Lollipop", "March 9 2015", "22", "ART"},
        {"6.0", "Marshmallow", "October 5 2015", "23", "ART"},
        {"7.0", "Nougat", "August 22 2016", "24", "ART"},
        {"7.1", "Nougat", "October 4 2016", "25", "ART"},
        {"8.0", "Oreo", "August 21 2017", "26", "ART"},
        {"8.1", "Oreo", "December 5 2017", "27", "ART"},
        {"9", "Pie", "August 6 2018", "28", "ART"},
        {"10", "10", "September 3 2019", "29", "ART"},
        {"11", "11", "September 8 2020", "30", "ART"},
        });

    table.SelectAll().Border(LIGHT);

    table.SelectColumn(0).Border(LIGHT);

    table.SelectRow(0).Decorate(bold);
    table.SelectRow(0).SeparatorVertical(LIGHT);
    table.SelectRow(0).Border(DOUBLE);

    table.SelectColumn(2).DecorateCells(align_right);

    auto content = table.SelectRows(1, -1);
    content.DecorateCellsAlternateRow(color(Color::Blue), 3, 0);
    content.DecorateCellsAlternateRow(color(Color::Cyan), 3, 1);
    content.DecorateCellsAlternateRow(color(Color::White), 3, 2);

    table.SelectCell(3, 4).Border(LIGHT, color(Color::Red));
    table.SelectCell(2, 7).Border(LIGHT, color(Color::Red));

    return text("\nWill be a page here soon\n");
}

ftxui::Element ProxyApp::options_page()
{
    return text("\nOptions page\n");
}

void ProxyApp::start() {

    auto screen = ftxui::ScreenInteractive::Fullscreen();
    auto header =
        hbox({
            text(" ProxyInterceptor ") | color(Color::Blue),
            filler(),
            text(" @github: leonardoLopesDev1908 ")
            }) | border;

    //Menu 
    std::vector<std::string> pages = {
        "[1] Manual;", "[2] Enter/Change endpoint;", "[3] Messages menu;",
        "[4] Options;","[5] Exit;"
    };
    menu = Menu({
         &pages,
         &selected,
    });

    //Endpoint input components
    inputHost = Input(&endpointState.host, "Host");
    inputPort = Input(&endpointState.port, "Port");

    inputPort |= CatchEvent([&](Event event) {
        return event.is_character() && !std::isdigit(event.character()[0]);
    });

    auto submitEndpoints = [&] {
        if(endpointState.host.empty() 
            || endpointState.port.empty())
        {
        }
        #ifdef _WIN32
            ProxyWindows proxy(endpointState.host, endpointState.port);
        #elif __linux__
            ProxyLinux proxy(endpointState.host, endpointState.port);
        #endif
        std::future<int> proxyLaunch = std::async(std::launch::async, [&proxy]{
            return proxy.start();        
        });
    };
    
    //auto btnSubmit = Button("Launch proxy", submitEndpoint, ButtonOption::Animated());

    input_container = Container::Vertical({
        inputHost,
        inputPort
    //    btnSubmit
    });

    main_container = Container::Tab({
        menu,
        input_container       
    }, &activeTab);

    //Message selection
    // messages_container = Menu({
    //     &messages,
    //     &messagesMenu.selectedMessage
    // });

    auto renderer = ftxui::Renderer(main_container, [&] {
        Element body;
        switch (activeTab)
        {
        case 0:
            body = manual_page();
            break;
        case 1:
            body = input_endpoint_page();
            break;
        case 2:
            body = messages_menu_page();
            break;
        case 3:
            body = options_page();
            break;  
        case 4:
            screen.ExitLoopClosure()();
            break;
        }

        return vbox({
           header,
           separator(),
           body | flex,
           separator(),
           menu->Render()
        });
    });

    auto app = CatchEvent(renderer, [&](Event event) {
        if(event == Event::Escape && activeTab != 0)
        {
            activeTab = 0;
            main_container->SetActiveChild(menu);
            return true;
        }

        if (event == Event::Return)
        {
            switch(selected)
            {
                case 1: 
                    activeTab = 1;
                    main_container->SetActiveChild(input_container);
                    return true;
                case 4:
                    screen.ExitLoopClosure()();
                    return true;
                default:
                    activeTab = selected;
                    return true; 
            }
        }
        return false;
    });
    screen.Loop(app);
}
