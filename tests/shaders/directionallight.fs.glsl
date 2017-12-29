#version 330 core

// Entrées du shader
in vec3 vPosition_vs; // Position du sommet transformé dans l'espace MVP
in vec3 vNormal_vs; // Normale du sommet transformé dans l'espace MVP
in vec2 vTexCoords; // Coordonnées de texture du sommet

out vec3 color;

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;
uniform  vec3 uLightDir_vs;
uniform vec3 uLightIntensity;

vec3 blinnPhong(){
    vec3 wi = normalize(uLightDir_vs);
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

   // vec3 res = uLightIntensity * (kd_wiN + kS_powShininess);
    vec3 res = uLightIntensity * (kd_wiN );

    return res;
}

vec3 blinnPhongLou(){
    vec3 wi = normalize(uLightDir_vs);
    vec3 wo = normalize(-vPosition_vs);
    vec3 half_vec = (wi+wo)/2.f;
    vec3 normal = normalize(vNormal_vs);
    float dot_wi_normal = (dot(wi,normal)>=0)? dot(wi,normal) : 0;
    float dot_half_normal = (dot(half_vec, normal)>=0)? dot(half_vec, normal) : 0;

    return uLightIntensity * (
        uKd * dot_wi_normal

        + uKs * pow(
            dot_half_normal,
            uShininess
            )

    );
}

void main() {

   color = blinnPhongLou();
   //color = vec3(255,0,0);
}