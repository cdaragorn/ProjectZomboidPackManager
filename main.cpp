#include "packmanagermainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ProjectZomboidPackManager::PackManagerMainWindow w;
    w.show();

    return a.exec();
}
