#ifndef DESIGNCOMWIDGET_H
#define DESIGNCOMWIDGET_H

#include<QWidget>
#include<QLayout>
#include<QVBoxLayout>
#include<QPushButton>
#include<QGridLayout>

class DesignComWidget : public QWidget
{
    Q_OBJECT
public:
    DesignComWidget();
private:
    QVBoxLayout* mainLayout;
    QGridLayout* componentLayout;
    void createAndAddComponentBtns();
};

#endif // DESIGNCOMWIDGET_H
