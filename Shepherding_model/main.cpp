#include "main_window.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");
    CMainWindow w;
    w.showMaximized();

    return a.exec();
}
