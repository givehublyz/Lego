#ifndef BUFFER_H
#define BUFFER_H
#include<qopenglfunctions_4_0_core.h>
#include<qvector.h>
template<class T>
class GLBuffer: public QVector<T>{
public:
    GLBuffer(){}
    void init(QOpenGLFunctions_4_0_Core* func, GLenum target){
        mFunc = func;
        mFunc->glGenBuffers(1, &mBufferId);
        mTarget = target;
    }
    void bind(){mFunc->glBindBuffer(mTarget, mBufferId);}
    void sendData(GLenum usage = GL_STATIC_DRAW){
        this->bind();
        mFunc->glBufferData(mTarget, sizeof(T) * this->size(), this->data(), usage);
    }
protected:
    QOpenGLFunctions_4_0_Core* mFunc;
    GLenum mTarget;
    GLuint mBufferId;
};

template<class T>
class GLVertAttriBuffer: public GLBuffer<T>{
public:
    GLVertAttriBuffer(){}
    void init(GLuint index, GLint attriSize, GLenum attriType,
              QOpenGLFunctions_4_0_Core* func, GLenum target){
        this->mVertAttriIndex = index;
        this->mVertAttriSize = attriSize;
        this->mVertAttriType = attriType;
        GLBuffer<T>::init(func, target);
        GLBuffer<T>::bind();
        this->mFunc->glEnableVertexAttribArray(index);
        this->mFunc->glVertexAttribPointer(index, attriSize, attriType, GL_FALSE, 0, nullptr);
    }
private:
    GLuint mVertAttriIndex;
    GLint mVertAttriSize;
    GLenum mVertAttriType;
};

#endif // BUFFER_H
