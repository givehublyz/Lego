#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QTabWidget>
#include<QLayout>
#include"design/designwidget.h"
#include"edit/editwidget.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    QTabWidget* tabWidget;
    DesignWidget* designWidget;
    EditWidget* editWidget;
};

#endif // MAINWINDOW_H
