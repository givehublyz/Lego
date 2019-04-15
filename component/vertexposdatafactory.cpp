#include "vertexposdatafactory.h"
#include<qmath.h>
#include<qdebug.h>
void VertexPosDataFactory::createCircle(float radius, float* buffer, size_t bufferOffset, size_t samples){
    //2pi / (samples+1);
    float delta = M_PI / (4 * (samples + 1));
    size_t ind = bufferOffset;
    for(int i = 1; i <= samples; i++){
        float deli = delta*i + delta / 2.0f;
        buffer[ind++] = radius * qCos(deli);
        buffer[ind++] = radius * qSin(deli);
        buffer[ind++] = 0.0f;
    }

    for(int i = samples - 1; i >= 0; i--){
        buffer[ind++] = buffer[i * 3 + 1];
        buffer[ind++] = buffer[i * 3];
        buffer[ind++] = 0.0f;
    }

    for(int i = 2 * samples - 1; i >= 0; i--){
        buffer[ind++] = -buffer[i * 3];
        buffer[ind++] = buffer[i * 3 + 1];
        buffer[ind++] = 0.0f;
    }

    for(int i = 4 * samples - 1; i >= 0; i--){
        buffer[ind++] = buffer[i * 3];
        buffer[ind++] = -buffer[i * 3 + 1];
        buffer[ind++] = 0.0f;
    }
//    for(int i = bufferOffset; i < bufferOffset + samples * 8 * 3; i+=3){
//        qDebug()<<buffer[i] << " "<<buffer[i+1]<<" "<<buffer[i+2];
//    }
}
