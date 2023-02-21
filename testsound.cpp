#include <QApplication>
#include "soundmanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    soundManager s;
    s.initialize();
    return a.exec();
}
