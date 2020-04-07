#include <cstdlib>
#include <iostream>
#include <exception>

#include <QtWidgets/QApplication>

#include <gui/include/gui_main.h>
#include <parser/include/reader.h>


int main(int argc, char *argv[]) 
{
    int ret = EXIT_SUCCESS;

    try {

        reader::Reader reader;
        QApplication app(argc, argv);
        GuiMain gui(reader);

        gui.show();

        ret = app.exec();
    }
    catch(std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
    catch(...) 
    {
        std::cerr << "Unexpected exception\n";
        exit(EXIT_FAILURE);
    }

    return ret;
}
