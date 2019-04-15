#include "designcomwidget.h"

DesignComWidget::DesignComWidget()
{
    mainLayout = new QVBoxLayout();
    componentLayout = new QGridLayout();
    mainLayout->addLayout(componentLayout);
    createAndAddComponentBtns();
    mainLayout->setAlignment(Qt::AlignTop);
    this->setLayout(mainLayout);
}

void DesignComWidget::createAndAddComponentBtns(){
    const int colNum = 4;
    int r = 0, c = 0;
    for(int i = 1; i <= 7; i++){
        for(int j = i; j <= 7; j++){
            QPushButton* btn = new QPushButton(QString::number(i) + "x" + QString::number(j));

            componentLayout->addWidget(btn, r, c);
            if(++c == colNum){
                c=0;
                r++;
            }
        }
    }
}
