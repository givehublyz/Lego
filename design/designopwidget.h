#ifndef DESIGNOPWIDGET_H
#define DESIGNOPWIDGET_H

#include<QSplitter>
#include"designcomwidget.h"

class DesignOpWidget : public QSplitter
{
    Q_OBJECT
public:
    DesignOpWidget();
private:
    DesignComWidget* comWidget;
};

#endif // DESIGNOPWIDGET_H
