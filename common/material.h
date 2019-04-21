#ifndef MATERIAL_H
#define MATERIAL_H
#include<qvector4d.h>

struct Material{
    QVector4D mAmbientColor;
    QVector4D mDiffuseColor;
    QVector4D mSpecularColor;
    float mSpecularIndex;
};

#endif // MATERIAL_H
