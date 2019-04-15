#include "mainwindow.h"
#include <QApplication>
#include"component/vertexposdatafactory.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    float* vpos = new float[3 * 4 * 8];
    VertexPosDataFactory::createCircle(0.5, vpos, 0);
    return a.exec();
}
