#version 330 core

// Entrées du shader
in vec3 vPosition_vs; // Position du sommet transformé dans l'espace MVP
in vec3 vNormal_vs; // Normale du sommet transformé dans l'espace MVP
in vec2 vTexCoords_vs; // Coordonnées de texture du sommet

out vec3 fsColor;

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;
uniform  vec3 uLightDir_vs_global_left;
uniform vec3 uLightIntensity_global_left;
uniform  vec3 uLightDir_vs_global_right;
uniform vec3 uLightIntensity_global_right;
uniform vec3 color;

uniform sampler2D uTexture;

vec3 blinnPhong(vec3 uLightDir_vs, vec3 uLightIntensity){
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

vec3 multiplyTexture(vec3 color, vec4 textureAlpha) {
    textureAlpha = textureAlpha * 0.8;
    color.x = color.x + 0.2;
    return color - textureAlpha.xyz;
}

void main() {

   fsColor = ( blinnPhong(uLightDir_vs_global_left,uLightIntensity_global_left) +
               blinnPhong(uLightDir_vs_global_right,uLightIntensity_global_right)
             ) *
             texture(uTexture, vTexCoords_vs).xyz *
             color ;

}