#version 400 core
in vec3 fNorm;
in vec3 fPos;
struct PointLight{
    float lightStrength;
    vec4 lightColor;
    vec3 lightPos;
};

struct Material{
    vec4 ambientColor;
    vec4 diffuseColor;
    vec4 specularColor;
    float specularIndex;
};

uniform PointLight uLight;
uniform Material uMaterial;
uniform vec3 uEyePos;

void main(){
    vec3 incidentLightDir = normalize(uLight.lightPos - fPos);
    vec3 reflectLightDir = reflect(incidentLightDir, fNorm);
    vec3 eyeDir = normalize(uEyePos - fPos);
    float dis = distance(uLight.lightPos, fPos);
    float attenuation = 1.0  / (dis * dis);
    float finalLightStrength = attenuation * uLight.lightStrength;
    //ambient comp
    vec4 ambComp = uMaterial.ambientColor;

    //diffuse comp
    float diffDot = dot(incidentLightDir, fNorm);
    vec4 diffComp = uMaterial.diffuseColor * uLight.lightColor
            * finalLightStrength * diffDot;

    //specular comp
    vec4 specComp = diffDot<=0.01? vec4(0.0) : uMaterial.specularColor * uLight.lightColor
            * finalLightStrength * pow(dot(eyeDir, reflectLightDir), uMaterial.specularIndex);
//    specComp = vec4(1.0);



    gl_FragColor = ambComp + diffComp + specComp;
}
