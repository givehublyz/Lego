#version 400 core
layout(location = 0)in vec3 vPos;
layout(location = 1)in vec3 vNorm;
uniform mat4 uProjection;
uniform mat4 uView;
out vec3 fNorm;
out vec3 fPos;
void main(){
    gl_Position = uProjection * uView * vec4(vPos, 1.0);
    fNorm = vNorm;
    fPos = vPos;
}
