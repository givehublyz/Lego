#ifndef DESIGNGLWIDGET_H
#define DESIGNGLWIDGET_H
#include<qopenglfunctions_4_0_core.h>
#include<QOpenGLWidget>
#include<qevent.h>
#include<qpoint.h>
#include<qcursor.h>
#include<qvector4d.h>
#include"common/mesh.h"
#include"common/shader.h"
#include"common/camera.h"
#include"common/light.h"
#include"common/material.h"
class DesignGLWidget : public QOpenGLWidget, public QOpenGLFunctions_4_0_Core
{
    Q_OBJECT
public:
    DesignGLWidget();

    virtual void initializeGL()Q_DECL_OVERRIDE;

    virtual void paintGL()Q_DECL_OVERRIDE;

    virtual void resizeGL(int width, int height)Q_DECL_OVERRIDE;
protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
protected slots:
    void update();
private:
    Mesh*mMesh;
    ShaderProgram* mProgram;

    //transform
    QMatrix4x4 mProjection;
    Camera mCamera;
    Uniform<QMatrix4x4>mViewUniform;
    Uniform<QMatrix4x4>mProjectionUniform;
    Uniform<QVector3D>mEyePosUniform;

    //point light
    PointLight mPointLight;
    Uniform<float>mLightStrengthUniform;
    Uniform<QVector4D>mLightColorUniform;
    Uniform<QVector3D>mLightPosUniform;

    //material
    Material mMaterial;
    Uniform<QVector4D>mAmbientColorUniform;
    Uniform<QVector4D>mDiffuseColorUniform;
    Uniform<QVector4D>mSpecularColorUniform;
    Uniform<float>mSpecularIndexUniform;

    struct InputManager{
        enum{KEY_A, KEY_D, KEY_Q, KEY_E, KEY_W, KEY_S, KEY_NUM};
        enum{BTN_LEFT, BTN_RIGHT, BTN_MIDDLE, BTN_NUM};
        bool mDownKey[KEY_NUM];
        bool mDownBtn[BTN_NUM];
        QPoint mLastCursorScreenPos;
        bool mHasStartedCapturePos;
        bool isKeyPressed(int key){return mDownKey[key];}
        bool isBtnPressed(int btn){return mDownBtn[btn];}
        void pressKey(int key){mDownKey[key] = true;}
        void releaseKey(int key){mDownKey[key] = false;}
        void pressBtn(int btn){mDownBtn[btn] = true;}
        void releaseBtn(int btn){mDownBtn[btn] = false;}
        bool hasStartedCapturePos(){return mHasStartedCapturePos;}
        void startCapturePos(){
            mLastCursorScreenPos = QCursor::pos();
            mHasStartedCapturePos = true;
        }
        void stopCapturePos(){mHasStartedCapturePos = false;}
        void update(){
            if(mHasStartedCapturePos)mLastCursorScreenPos = QCursor::pos();
        }
        QPoint getPosDiff(){return QCursor::pos() - mLastCursorScreenPos;}
        InputManager(){
            mHasStartedCapturePos = false;
            memset(mDownKey, false, sizeof(mDownKey));
            memset(mDownBtn, false, sizeof(mDownBtn));
        }
    }mInput;

    void buildShaderProgram();
};

#endif // DESIGNGLWIDGET_H
