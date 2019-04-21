#ifndef LIGHT_H
#define LIGHT_H
#include<qvector4d.h>
#include<qvector3d.h>
struct Light{
    float mLightStrength;
    QVector4D mLightColor;
};

struct PointLight:Light{
    QVector3D mLightPos;
};

#endif // LIGHT_H
