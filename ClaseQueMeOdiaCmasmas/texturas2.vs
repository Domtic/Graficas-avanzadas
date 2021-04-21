#version 330 core
out vec4 FragColor;

in vec3 nuestroColor;
in vec2 nuestraTextura;

//textura
uniform sampler2D textura1;
uniform sampler2D textura2;

void main()
{
FragColor = mix(texture(textura1, nuestraTextura), texture(textura2, nuestraTextura), 1.0) * vec4(nuestroColor, 1.0);
}