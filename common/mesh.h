#ifndef MESH_H
#define MESH_H
#include<qvector3d.h>
#include<qopenglfunctions_4_0_core.h>
#include"buffer.h"
#include<qfile.h>
#include<qdebug.h>
class Mesh;
class Object3D{
    friend class Mesh;
public:
    Object3D(const char* filename);
private:
    QVector<QVector3D>mPos;
    QVector<QVector3D>mNorm;
    struct Face{
        QVector<int>mPosIndex;
        QVector<int>mNormIndex;
    };
    QVector<Face>mFace;
    void loadObj(const char* filename);
    void parseVPos(QString str);
    void parseVNor(QString str);
    void parseFace(QString str);
};

class Mesh
{
public:
    Mesh(const char* filename);
    GLVertAttriBuffer<QVector3D> mPosBuffer;
    GLVertAttriBuffer<QVector3D> mNormBuffer;
};

#endif // MESH_H
