#include "designwidget.h"

DesignWidget::DesignWidget()
{
    glWidget = new DesignGLWidget();
    opWidget = new DesignOpWidget();
    this->addWidget(glWidget);
    this->addWidget(opWidget);
    this->setStretchFactor(0, 1);
    this->setStretchFactor(1, 1);
}

QString DesignWidget::getName(){
    return QString::fromLocal8Bit("搭积木");
}
