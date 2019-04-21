#include "camera.h"
QVector3D Camera::sGlobalForward(0.0, 0.0, -1.0);
QVector3D Camera::sGlobalRightward(1.0, 0.0, 0.0);
QVector3D Camera::sGlobalUpward(0.0, 1.0, 0.0);

Camera::Camera()
{
    mView.setToIdentity();
    mDirty = true;
    mAutoUpdate = true;
}

void Camera::moveForward(float dis){
    mDirty = true;
    mTranslate += getLocalForward() * dis;
    if(mAutoUpdate)updateViewMat();
}

void Camera::moveRightward(float dis){
    mDirty = true;
    mTranslate += getLocalRightward() * dis;
    if(mAutoUpdate)updateViewMat();
}

void Camera::moveUpward(float dis){
    mDirty = true;
    mTranslate += sGlobalUpward * dis;
    if(mAutoUpdate)updateViewMat();
}

void Camera::yaw(float angle){
    mDirty = true;
    mRotate *= QQuaternion::fromAxisAndAngle(sGlobalUpward, angle);
    if(mAutoUpdate)updateViewMat();
}

void Camera::pitch(float angle){
    mDirty = true;
    mRotate *= QQuaternion::fromAxisAndAngle(sGlobalRightward, angle);
    if(mAutoUpdate)updateViewMat();
}

const QMatrix4x4& Camera::getViewMat(){
    updateViewMat();
    return mView;
}

const QVector3D& Camera::getEyePos(){
    return mTranslate;
}

void Camera::updateViewMat(){
    if(mDirty){
        mView.setToIdentity();
        mView.rotate(mRotate.conjugated());
        mView.translate(-mTranslate);
        mDirty = false;
    }
}

QVector3D Camera::getLocalForward(){
    return mRotate.rotatedVector(sGlobalForward);
}

QVector3D Camera::getLocalRightward(){
    return mRotate.rotatedVector(sGlobalRightward);
}

QVector3D Camera::getLocalUpward(){
    return mRotate.rotatedVector(sGlobalUpward);
}

void Camera::setAutoUpdate(bool autoUpdate){
    mAutoUpdate = autoUpdate;
}
