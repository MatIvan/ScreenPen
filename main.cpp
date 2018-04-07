#include "fullscreen.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FullScreen FullScreenWindow;
    FullScreenWindow.show();

    return a.exec();
}
