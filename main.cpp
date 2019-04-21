#include "mainwindow.h"
#include <QApplication>
#include"component/vertexposdatafactory.h"
#include"common/buffer.h"
#include<qdebug.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
