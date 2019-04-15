#ifndef VERTEXPOSDATAFACTORY_H
#define VERTEXPOSDATAFACTORY_H


class VertexPosDataFactory
{
private:
public:
    static void createCircle(float radius, float* buffer, size_t bufferOffset, size_t samples = 4);
};

#endif // VERTEXPOSDATAFACTORY_H
