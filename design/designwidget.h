#ifndef DESIGNWIDGET_H
#define DESIGNWIDGET_H

#include<QWidget>
#include<QSplitter>
#include<QString>
#include"designglwidget.h"
#include"designopwidget.h"

class DesignWidget : public QSplitter
{
    Q_OBJECT
public:
    DesignWidget();
    QString getName();
private:
    DesignGLWidget* glWidget;
    DesignOpWidget* opWidget;
};

#endif // DESIGNWIDGET_H
