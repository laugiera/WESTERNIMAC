#version 330 core

// Entrées du shader
in vec3 vPosition_vs; // Position du sommet transformé dans l'espace MVP
in vec3 vNormal_vs; // Normale du sommet transformé dans l'espace MVP
in vec2 vTexCoords_vs; // Coordonnées de texture du sommet

out vec3 fsColor;

uniform vec3 color;

uniform sampler2D uTexture;


void main() {

   fsColor =   texture(uTexture, vTexCoords_vs).xyz *
                                     color ;
}