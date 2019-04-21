#include "designglwidget.h"

#include<qwidget.h>
#include<qlayout.h>
#include<QVBoxLayout>
#include<QPushButton>
#include<QSpacerItem>
#include<QSlider>
#include<QLabel>
#include<QGridLayout>
#include<vector>
#include<qcolordialog.h>
using std::vector;

DesignGLWidget::DesignGLWidget()
{
    mProgram = nullptr;
    mMesh = new Mesh(":/model/teapot.obj");
    mPointLight.mLightPos = QVector3D(2,2,2);
    mPointLight.mLightColor = QVector4D(1, 1, 1, 1);
    mPointLight.mLightStrength = 1.0;

    mMaterial.mAmbientColor = mMaterial.mDiffuseColor = mMaterial.mSpecularColor = QVector4D(0.3, 0.6, 0.9, 1.0);
    mMaterial.mSpecularIndex = 30;


    QWidget* console = new QWidget();
    QGridLayout* conLayout = new QGridLayout();
    QPushButton* rebuildShaderProgramBtn = new QPushButton(tr("Rebuild Shader Program"));
    QLabel* lightStrengthLabel = new QLabel(tr("light strength"));
    QSlider* ligthStrengthSlider = new QSlider();
    QLabel* lightColorLabel = new QLabel(tr("light color"));
    QPushButton* lightColorBtn = new QPushButton(tr("light color"));
    QLabel* ligthPosXLabel = new QLabel(tr("light pos x"));
    QLabel* ligthPosYLabel = new QLabel(tr("light pos y"));
    QLabel* ligthPosZLabel = new QLabel(tr("light pos z"));
    QSlider* lightPosXSlider = new QSlider();
    QSlider* lightPosYSlider = new QSlider();
    QSlider* lightPosZSlider = new QSlider();


    int r = 0;

    conLayout->addWidget(rebuildShaderProgramBtn, r++, 0, 1, 2);
    conLayout->addWidget(lightStrengthLabel, r, 0);
    conLayout->addWidget(ligthStrengthSlider, r++, 1);

    conLayout->addWidget(lightColorLabel, r, 0);
    conLayout->addWidget(lightColorBtn, r++, 1);

    conLayout->addWidget(ligthPosXLabel, r, 0);
    conLayout->addWidget(lightPosXSlider, r++, 1);
    conLayout->addWidget(ligthPosYLabel, r, 0);
    conLayout->addWidget(lightPosYSlider, r++, 1);
    conLayout->addWidget(ligthPosZLabel, r, 0);
    conLayout->addWidget(lightPosZSlider, r++, 1);


    vector<const char*>btnName{"amb color", "diff color", "spec color"};
    vector<QVector4D*>colorAttr{&mMaterial.mAmbientColor, &mMaterial.mDiffuseColor, &mMaterial.mSpecularColor};
    for(int i = 0; i < btnName.size(); i++){
        conLayout->addWidget(new QLabel(btnName[i]), r, 0);
        QPushButton* btn = new QPushButton(btnName[i]);
        conLayout->addWidget(btn, r++, 1);
        connect(btn, &QPushButton::clicked, [=]{
            QColorDialog dialog;
            QColor color = dialog.getColor();
            colorAttr[i]->setX(color.redF());
            colorAttr[i]->setY(color.greenF());
            colorAttr[i]->setZ(color.blueF());
            colorAttr[i]->setW(color.alphaF());
        });
    }

    QLabel* specularIndexLabel = new QLabel(tr("spec index"));
    QSlider* specSlider = new QSlider();
    conLayout->addWidget(specularIndexLabel, r, 0);
    conLayout->addWidget(specSlider, r++, 1);

    vector<int>mins{0, -50, -50, -50, -150};
    vector<int>maxs{50, 50, 50, 50, 150};
    vector<int>inters{1, 10, 10, 10, 1};
    float lightStrenRange = 1;
    float xyzRange = 10;
    float specIndexRange = 1;
    PointLight* pPointLight = &mPointLight;
    Material* pMaterial = &mMaterial;
    vector<QSlider*>sliders{ligthStrengthSlider, lightPosXSlider, lightPosYSlider, lightPosZSlider, specSlider};

    for(int i = 0; i < sliders.size(); i++){
        sliders[i]->setMinimum(mins[i]);
        sliders[i]->setMaximum(maxs[i]);
        sliders[i]->setTickInterval(inters[i]);
        sliders[i]->setTickPosition(QSlider::TicksBelow);
        sliders[i]->setOrientation(Qt::Horizontal);
    }
    connect(ligthStrengthSlider, &QSlider::sliderMoved, [=]{
        pPointLight->mLightStrength = ligthStrengthSlider->value() / (lightStrenRange);
    });

    connect(lightPosXSlider, &QSlider::sliderMoved, [=]{
        pPointLight->mLightPos.setX(lightPosXSlider->value() / (xyzRange));
    });

    connect(lightPosYSlider, &QSlider::sliderMoved, [=]{
         pPointLight->mLightPos.setY(lightPosYSlider->value() / (xyzRange));
    });

    connect(lightPosZSlider, &QSlider::sliderMoved, [=]{
         pPointLight->mLightPos.setZ(lightPosZSlider->value() / (xyzRange));
    });

    connect(specSlider, &QSlider::sliderMoved, [=]{
        pMaterial->mSpecularIndex = specSlider->value() / (specIndexRange);
    });


    connect(lightColorBtn, &QPushButton::clicked, [=]{
        QColorDialog dialog;
        QColor color = dialog.getColor();
        pPointLight->mLightColor.setX(color.redF());
        pPointLight->mLightColor.setY(color.greenF());
        pPointLight->mLightColor.setZ(color.blueF());
        pPointLight->mLightColor.setW(color.alphaF());
    });

    connect(rebuildShaderProgramBtn, &QPushButton::clicked, [&]{
        mProgram->requestRebuild();
    });

    console->setLayout(conLayout);
    console->show();
}

void DesignGLWidget::initializeGL(){
    initializeOpenGLFunctions();
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
    GLuint objId;
    this->glGenVertexArrays(1,&objId);
    this->glBindVertexArray(objId);
    mMesh->mPosBuffer.init(0, 3, GL_FLOAT, this, GL_ARRAY_BUFFER);
    mMesh->mPosBuffer.sendData();
    mMesh->mNormBuffer.init(1, 3, GL_FLOAT, this, GL_ARRAY_BUFFER);
    mMesh->mNormBuffer.sendData();

    this->buildShaderProgram();
}

void DesignGLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mMesh->mPosBuffer.bind();

    if(mProgram->needRebuild()){
        this->buildShaderProgram();
    }

    mProgram->use();
    //transform
    mProgram->setUniform(mProjectionUniform);
    mProgram->setUniform(mViewUniform);
    mProgram->setUniform(mEyePosUniform);
    //point light
    mProgram->setUniform(mLightPosUniform);
    mProgram->setUniform(mLightColorUniform);
    mProgram->setUniform(mLightStrengthUniform);
    //material
    mProgram->setUniform(mAmbientColorUniform);
    mProgram->setUniform(mDiffuseColorUniform);
    mProgram->setUniform(mSpecularColorUniform);
    mProgram->setUniform(mSpecularIndexUniform);

    this->glDrawArrays(GL_TRIANGLES, 0, mMesh->mPosBuffer.size());
}

void DesignGLWidget::resizeGL(int width, int height){
    mProjection.setToIdentity();
    mProjection.perspective(45.0f, float(width)/float(height), 0.1f, 100.0f);
}

void DesignGLWidget::update(){
    float moveStepLen = 0.1f;
    if(mInput.isKeyPressed(InputManager::KEY_S)){
        mCamera.moveForward(-moveStepLen);
    }
    if(mInput.isKeyPressed(InputManager::KEY_W)){
        mCamera.moveForward(moveStepLen);
    }
    if(mInput.isKeyPressed(InputManager::KEY_A)){
        mCamera.moveRightward(-moveStepLen);
    }
    if(mInput.isKeyPressed(InputManager::KEY_D)){
        mCamera.moveRightward(moveStepLen);
    }
    if(mInput.isKeyPressed(InputManager::KEY_Q)){
        mCamera.moveUpward(-moveStepLen);
    }
    if(mInput.isKeyPressed(InputManager::KEY_E)){
        mCamera.moveUpward(moveStepLen);
    }

    float rotAngle = 0.1;
    if(mInput.isBtnPressed(InputManager::BTN_LEFT)){
        if(!mInput.hasStartedCapturePos()){
            mInput.startCapturePos();
        }
        else{
            QPoint diff = mInput.getPosDiff();
            if(diff.x() != 0){
                mCamera.yaw(rotAngle * float(-diff.x()));
            }
            if(diff.y() != 0){
                mCamera.pitch(rotAngle * float(-diff.y()));
            }
        }
    }
    else{
        mInput.stopCapturePos();
    }
    mInput.update();
    QOpenGLWidget::update();
}



void DesignGLWidget::mousePressEvent(QMouseEvent* event){
    this->setFocus();
    switch(event->button()){
    case Qt::LeftButton:{
        mInput.pressBtn(InputManager::BTN_LEFT);
        break;
    }
    case Qt::MiddleButton:{
        mInput.pressBtn(InputManager::BTN_MIDDLE);
        break;
    }
    case Qt::RightButton:{
        mInput.pressBtn(InputManager::BTN_RIGHT);
        break;
    }
    }
    QOpenGLWidget::mousePressEvent(event);
}
void DesignGLWidget::mouseReleaseEvent(QMouseEvent* event){
    switch(event->button()){
    case Qt::LeftButton:{
        mInput.releaseBtn(InputManager::BTN_LEFT);
        break;
    }
    case Qt::MiddleButton:{
        mInput.releaseBtn(InputManager::BTN_MIDDLE);
        break;
    }
    case Qt::RightButton:{
        mInput.releaseBtn(InputManager::BTN_RIGHT);
        break;
    }
    }
    QOpenGLWidget::mouseReleaseEvent(event);
}
void DesignGLWidget::keyPressEvent(QKeyEvent* event){
    switch(event->key()){
    case Qt::Key_A:{
        mInput.pressKey(InputManager::KEY_A);
        break;
    }
    case Qt::Key_S:{
        mInput.pressKey(InputManager::KEY_S);
        break;
    }
    case Qt::Key_D:{
        mInput.pressKey(InputManager::KEY_D);
        break;
    }
    case Qt::Key_Q:{
        mInput.pressKey(InputManager::KEY_Q);
        break;
    }
    case Qt::Key_W:{
        mInput.pressKey(InputManager::KEY_W);
        break;
    }
    case Qt::Key_E:{
        mInput.pressKey(InputManager::KEY_E);
        break;
    }
    }
    QOpenGLWidget::keyPressEvent(event);
}
void DesignGLWidget::keyReleaseEvent(QKeyEvent* event){
    switch(event->key()){
    case Qt::Key_A:{
        mInput.releaseKey(InputManager::KEY_A);
        break;
    }
    case Qt::Key_S:{
        mInput.releaseKey(InputManager::KEY_S);
        break;
    }
    case Qt::Key_D:{
        mInput.releaseKey(InputManager::KEY_D);
        break;
    }
    case Qt::Key_Q:{
        mInput.releaseKey(InputManager::KEY_Q);
        break;
    }
    case Qt::Key_W:{
        mInput.releaseKey(InputManager::KEY_W);
        break;
    }
    case Qt::Key_E:{
        mInput.releaseKey(InputManager::KEY_E);
        break;
    }
    }
    QOpenGLWidget::keyReleaseEvent(event);
}

void DesignGLWidget::buildShaderProgram(){
    if(mProgram != nullptr){
        delete mProgram;
    }
    mProgram = ShaderProgramFactory::createSimpleShaderProgram(this, "C:/Users/lgh/Documents/QtProjects/LEGO/shaders/simple_vsh.vsh", "C:/Users/lgh/Documents/QtProjects/LEGO/shaders/simple_fsh.frag");
    //transform
    mProjectionUniform = mProgram->getUniform<QMatrix4x4>("uProjection");
    mViewUniform = mProgram->getUniform<QMatrix4x4>("uView");
    mEyePosUniform = mProgram->getUniform<QVector3D>("uEyePos");

    mProjectionUniform.bindData(&mProjection);
    mViewUniform.bindData(&mCamera.getViewMat());
    mEyePosUniform.bindData(&mCamera.getEyePos());

    //point light
    mLightStrengthUniform = mProgram->getUniform<float>("uLight.lightStrength");
    mLightColorUniform = mProgram->getUniform<QVector4D>("uLight.lightColor");
    mLightPosUniform = mProgram->getUniform<QVector3D>("uLight.lightPos");

    mLightStrengthUniform.bindData(&mPointLight.mLightStrength);
    mLightColorUniform.bindData(&mPointLight.mLightColor);
    mLightPosUniform.bindData(&mPointLight.mLightPos);

    //material
    mAmbientColorUniform = mProgram->getUniform<QVector4D>("uMaterial.ambientColor");
    mDiffuseColorUniform = mProgram->getUniform<QVector4D>("uMaterial.diffuseColor");
    mSpecularColorUniform = mProgram->getUniform<QVector4D>("uMaterial.specularColor");
    mSpecularIndexUniform = mProgram->getUniform<float>("uMaterial.specularIndex");

    mAmbientColorUniform.bindData(&mMaterial.mAmbientColor);
    mDiffuseColorUniform.bindData(&mMaterial.mDiffuseColor);
    mSpecularColorUniform.bindData(&mMaterial.mSpecularColor);
    mSpecularIndexUniform.bindData(&mMaterial.mSpecularIndex);
}
