#include "shader.h"

Shader::Shader(QOpenGLFunctions_4_0_Core* func, const char* filename, GLenum shaderType)
    :mFunc(func), mShaderType(shaderType){
    mShaderID = mFunc->glCreateShader(shaderType);
    compile(filename);
}

void Shader::destroy(){mFunc->glDeleteShader(mShaderID);}

void Shader::compile(const char *filename){
    //读取代码
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<<"Can't open the file: "<<filename<<endl;
        return;
    }
    QString qcode = file.readAll();
    file.close();
    if(qcode.isEmpty()){
        qDebug()<<"read vsh file error";
        return;
    }
    std::string code = qcode.toStdString();
    //编译
    qDebug("Compiling shader : %s\n", filename);
    char const * pSrc = code.c_str();
    mFunc->glShaderSource(mShaderID, 1, &pSrc , nullptr);
    mFunc->glCompileShader(mShaderID);
    //检查
    GLint Result = GL_FALSE;
    int InfoLogLength;
    mFunc->glGetShaderiv(mShaderID, GL_COMPILE_STATUS, &Result);
    mFunc->glGetShaderiv(mShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
        mFunc->glGetShaderInfoLog(mShaderID, InfoLogLength, nullptr, &VertexShaderErrorMessage[0]);
        qDebug("%s\n", &VertexShaderErrorMessage[0]);
    }
}

ShaderProgram::ShaderProgram(QOpenGLFunctions_4_0_Core* func):mFunc(func), mNeedRebuild(true){
    mProgramID = mFunc->glCreateProgram();
}

void ShaderProgram::attachShader(const Shader &shader){
    mFunc->glAttachShader(mProgramID, shader.mShaderID);
}

void ShaderProgram::detachShader(const Shader &shader){
    mFunc->glDetachShader(mProgramID, shader.mShaderID);
}

void ShaderProgram::link(){
    mFunc->glLinkProgram(mProgramID);
    mNeedRebuild = false;
    //检查
    GLint Result = GL_FALSE;
    int InfoLogLength;
    mFunc->glGetProgramiv(mProgramID, GL_LINK_STATUS, &Result);
    mFunc->glGetProgramiv(mProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> ProgramErrorMessage(InfoLogLength+1);
        mFunc->glGetProgramInfoLog(mProgramID, InfoLogLength, nullptr, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }
}

GLuint ShaderProgram::getProgramID(){return mProgramID;}

void ShaderProgram::setUniform(const Uniform<QMatrix4x4>& uniform){
    mFunc->glUniformMatrix4fv(uniform.mLocation, 1, GL_FALSE, uniform.mData->data());
}

void ShaderProgram::setUniform(const Uniform<QVector3D>& uniform){
    mFunc->glUniform3fv(uniform.mLocation, 1, (GLfloat*)uniform.mData);
}

void ShaderProgram::setUniform(const Uniform<float>& uniform){
    mFunc->glUniform1fv(uniform.mLocation, 1, uniform.mData);
}

void ShaderProgram::setUniform(const Uniform<QVector4D>& uniform){
    mFunc->glUniform4fv(uniform.mLocation, 1, (GLfloat*)uniform.mData);
}

ShaderProgram* ShaderProgramFactory::createSimpleShaderProgram(QOpenGLFunctions_4_0_Core *func, const char *vshFilename, const char *fshFilename){
    ShaderProgram* program = new ShaderProgram(func);
    Shader vShader(func, vshFilename, GL_VERTEX_SHADER);
    Shader fShader(func, fshFilename, GL_FRAGMENT_SHADER);
    program->attachShader(vShader);
    program->attachShader(fShader);
    program->link();
    program->detachShader(vShader);
    program->detachShader(fShader);
    vShader.destroy();
    fShader.destroy();
    return program;
}

void ShaderProgram::use(){mFunc->glUseProgram(mProgramID);}

void ShaderProgram::requestRebuild(){mNeedRebuild = true;}

bool ShaderProgram::needRebuild(){return mNeedRebuild;}

ShaderProgram::~ShaderProgram(){
    mFunc->glDeleteProgram(mProgramID);
}
