#include "mesh.h"
Object3D::Object3D(const char* filename){
    loadObj(filename);
}

void Object3D::loadObj(const char* filename){
    QFile file(filename);
    if(!file.open(QIODevice::Text | QIODevice::ReadOnly)){
        qDebug()<<"open file error";
        return;
    }

    QString str = file.readAll();
    QStringList qsl = str.split("\n", QString::SplitBehavior::SkipEmptyParts);
    for(auto s : qsl){
        if(s.startsWith("vn ")){
            parseVNor(s);
        }
        else if(s.startsWith("v ")){
            parseVPos(s);
        }
        else if(s.startsWith("f ")){
            parseFace(s);
        }
    }
}

void Object3D::parseVPos(QString str){
   QStringList strs = str.split(" ", QString::SplitBehavior::SkipEmptyParts);
   if(strs.size() != 4)return;
   mPos.append(QVector3D(strs[1].toFloat(), strs[2].toFloat(), strs[3].toFloat()));
}

void Object3D::parseVNor(QString str){
    QStringList strs = str.split(" ", QString::SplitBehavior::SkipEmptyParts);
    if(strs.size() != 4)return;
    mNorm.append(QVector3D(strs[1].toFloat(), strs[2].toFloat(), strs[3].toFloat()));
}

void Object3D::parseFace(QString str){
    QStringList strs = str.split(" ", QString::SplitBehavior::SkipEmptyParts);
    if(strs.size() != 4)return;
    Face f;
    for(int i = 1; i < strs.size(); i++){
        QStringList strs2 = strs[i].split("/", QString::SplitBehavior::KeepEmptyParts);
        GLuint posInd = strs2[0].toUInt() - 1;
        GLuint norInd = strs2[2].toUInt() - 1;
        f.mPosIndex.push_back(posInd);
        f.mNormIndex.push_back(norInd);
        mFace.push_back(f);
    }
}

Mesh::Mesh(const char* filename)
{
    Object3D obj(filename);
    QVector<Object3D::Face>& faces = obj.mFace;
    QVector<QVector3D>& poses = obj.mPos;
    QVector<QVector3D>& normes = obj.mNorm;
    for(int i = 0; i < faces.size(); i++){
        QVector<int>& posIndices = faces[i].mPosIndex;
        QVector<int>& normIndices = faces[i].mNormIndex;
        for(int j : posIndices){
            mPosBuffer.push_back(poses[j]);
        }
        for(int j : normIndices){
            mNormBuffer.push_back(normes[j]);
        }
    }
}
