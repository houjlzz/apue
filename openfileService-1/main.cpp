#include <QCoreApplication>
extern "C"{
#include "../Ourhdr/ourhdr.h"
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    return a.exec();
}
