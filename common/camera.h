#ifndef CAMERA_H
#define CAMERA_H
#include<qvector3d.h>
#include<qquaternion.h>
#include<qmatrix4x4.h>
class Camera
{
public:
    Camera();
    void moveForward(float dis);
    void moveRightward(float dis);
    void moveUpward(float dis);
    void yaw(float angle);
    void pitch(float angle);
    const QMatrix4x4& getViewMat();
    const QVector3D& getEyePos();
    void updateViewMat();
    void setAutoUpdate(bool autoUpdate);
    static QVector3D sGlobalForward;
    static QVector3D sGlobalRightward;
    static QVector3D sGlobalUpward;
    QVector3D getLocalForward();
    QVector3D getLocalRightward();
    QVector3D getLocalUpward();
private:
    QVector3D mTranslate;
    QQuaternion mRotate;
    QMatrix4x4 mView;
    bool mDirty;
    bool mAutoUpdate;
};

#endif // CAMERA_H
