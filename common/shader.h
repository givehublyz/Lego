#ifndef SHADER_H
#define SHADER_H
#include<qopenglfunctions_4_0_core.h>
#include<qmatrix4x4.h>
#include<qfile.h>
#include<qdebug.h>
class Shader
{
    friend class ShaderProgram;
public:
    Shader(QOpenGLFunctions_4_0_Core* func, const char* filename, GLenum shaderType);
    void destroy();
private:
    QOpenGLFunctions_4_0_Core* mFunc;
    GLuint mShaderID;
    GLenum mShaderType;
    void compile(const char* filename);
};

template<class T>
struct Uniform{
    GLint mLocation;
    const T* mData;
    Uniform(){}
    Uniform(GLint location):mLocation(location){}
    void bindData(const T *const data){mData = data;}
};

class ShaderProgram{
public:
    ShaderProgram(QOpenGLFunctions_4_0_Core* func);
    void attachShader(const Shader& shader);
    void link();
    void detachShader(const Shader& shader);
    GLuint getProgramID();
    template<class T>
    Uniform<T> getUniform(const char* uniformName){
        return Uniform<T>(mFunc->glGetUniformLocation(mProgramID, uniformName));
    }
    void setUniform(const Uniform<QMatrix4x4>& uniform);
    void setUniform(const Uniform<QVector3D>& uniform);
    void setUniform(const Uniform<float>& uniform);
    void setUniform(const Uniform<QVector4D>& uniform);
    void use();
    void requestRebuild();
    bool needRebuild();
    ~ShaderProgram();
private:
    QOpenGLFunctions_4_0_Core* mFunc;
    GLuint mProgramID;
    bool mNeedRebuild;
};

class ShaderProgramFactory{
public:
    static ShaderProgram* createSimpleShaderProgram(QOpenGLFunctions_4_0_Core* func, const char* vshFilename, const char* fshFilename);
};

#endif // SHADER_H
