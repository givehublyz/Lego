#include "designopwidget.h"

DesignOpWidget::DesignOpWidget()
{
    comWidget = new DesignComWidget();
    this->addWidget(comWidget);
}
