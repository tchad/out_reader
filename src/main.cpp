#include <iostream>

#include <QtWidgets/QApplication>

#include <gui/include/gui_main.h>
#include <parser/include/reader.h>


int main(int argc, char *argv[]) 
{
    int ret = 0;

    try {

        reader::Reader reader;
        reader.LoadFile("a1", "b1", "v1");
        reader.LoadFile("a2", "b2", "v2");
        reader.LoadFile("a3", "b3", "v3");
        reader.LoadFile("a4", "b4", "v4");

        QApplication app(argc, argv);

        GuiMain gui(reader);
        gui.show();

        ret = app.exec();
    }
    catch(...) 
    {
        std::cerr << "Unexpected exception\n";
        ret = -1;
    }

    return ret;
}
