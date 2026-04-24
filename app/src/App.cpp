#include <ftxui/screen/color.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/table.hpp>
#include <iostream>
#include <stdlib.h>
#include <thread>

int main() {
    using namespace ftxui;

    auto screen = Screen::Create(Dimension::Full());

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

    // Add border around the first column.
    table.SelectColumn(0).Border(LIGHT);

    // Make first row bold with a double border.
    table.SelectRow(0).Decorate(bold);
    table.SelectRow(0).SeparatorVertical(LIGHT);
    table.SelectRow(0).Border(DOUBLE);

    // Align right the "Release date" column.
    table.SelectColumn(2).DecorateCells(align_right);

    // Select row from the second to the last.
    auto content = table.SelectRows(1, -1);
    // Alternate in between 3 colors.
    content.DecorateCellsAlternateRow(color(Color::Blue), 3, 0);
    content.DecorateCellsAlternateRow(color(Color::Cyan), 3, 1);
    content.DecorateCellsAlternateRow(color(Color::White), 3, 2);

    // Decorate 2 random cells with a red border.
    table.SelectCell(3, 4).Border(LIGHT, color(Color::Red));
    table.SelectCell(2, 7).Border(LIGHT, color(Color::Red));

    while(true)
    {
        auto document = table.Render();
        
        Render(screen, document);
        std::cout << screen.ResetPosition();
        screen.Print();
        auto reset_ui = screen.ResetPosition();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

  std::cout << std::endl;
}



/*int main(int argc, char *argv[])
{
	if (argc != 2) {
		std::cout << "Arguments missing. Execution example:\n";
		std::cout << "./Proxy 127.0.0.1 8080\n";
		return 1;
	}

	std::string host = argv[1];
	int port = atoi(argv[2]);

    //Resolve cross-platform to
    //choose what Proxy to launch
    //
    //std::thread proxyThread(proxy.create())
    
    //Launch concurrent proxy at endpoint
    //Main thread runs App and waits for user input
    /*
     * User main options:
     *  Show Queue of messages
     *  Chose message
     *  End app
    */

    /* User message options:
     *  Show request/response
     *  Edit request/response
     *  Forward
    */

//	return 0;
//}
