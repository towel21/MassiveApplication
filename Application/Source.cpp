#include <QtWidgets/QApplication>
#include "Window.hpp"

int main(int argc,char **argv)
{
    QApplication app(argc,argv);

    MyWindow window;

    return app.exec();
}