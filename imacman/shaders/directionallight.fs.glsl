#version 330 core

// Entrées du shader
in vec3 vPosition_vs; // Position du sommet transformé dans l'espace MVP
in vec3 vNormal_vs; // Normale du sommet transformé dans l'espace MVP
in vec2 vTexCoords; // Coordonnées de texture du sommet

out vec3 fsColor;

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;
uniform  vec3 uLightDir_vs;
uniform vec3 uLightIntensity;
uniform vec3 color;

vec3 blinnPhong(){
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

   fsColor = blinnPhong() * color;
}