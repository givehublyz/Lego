#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    tabWidget = new QTabWidget();
    designWidget = new DesignWidget();
    editWidget = new EditWidget();
    tabWidget->insertTab(0, designWidget, designWidget->getName());
    tabWidget->insertTab(1, editWidget, editWidget->getName());
    this->setCentralWidget(tabWidget);
    this->setWindowState(Qt::WindowMaximized);
}

MainWindow::~MainWindow()
{

}
