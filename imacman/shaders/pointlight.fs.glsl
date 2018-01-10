/*
#version 330 core

// Entrées du shader
in vec3 vPosition_vs; // Position du sommet transformé dans l'espace MVP
in vec3 vNormal_vs; // Normale du sommet transformé dans l'espace MVP
in vec2 vTexCoords; // Coordonnées de texture du sommet

out vec3 fsColor;

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;
uniform  vec3 uLightDir_vs_global;
uniform vec3 uLightIntensity_global;
uniform  vec3 uLightDir_vs_player;
uniform vec3 uLightIntensity_player;
uniform vec3 color;

vec3 blinnPhong(){
    vec3 wi = (normalize(uLightPos_vs - vPosition_vs));
    vec3 w0 = normalize(-vPosition_vs);
    vec3 halfVector = normalize((w0+wi)/2.0);
    vec3 normals = normalize(vNormal_vs);

    float wiN = dot(wi,normals);
    if(wiN < 0)
        wiN = 0;
    float halfVectorN = dot(halfVector,normals);
    if(halfVectorN <0)
        halfVectorN = 0;
    float powShininess = pow(halfVectorN,uShininess);
    vec3 kS_powShininess = uKs*powShininess;
    vec3 kd_wiN = uKd*wiN;

    float d = distance(uLightPos_vs,vPosition_vs);
    //uLightIntensity = (uLightIntensity / (d * d));
    vec3 res = (uLightIntensity / (d * d)) * (kd_wiN );

    return res;
}

void main() {

   color = blinnPhong() * color;
   }
*/
