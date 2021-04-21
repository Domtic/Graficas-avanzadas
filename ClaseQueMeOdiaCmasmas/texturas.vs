#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;


out vec3 nuestroColor;
out vec2 nuestraTextura;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 transform;
uniform vec3 color;
void main(){
		gl_Position =  transform * vec4(aPos, 1.0);
		nuestroColor = color *aColor;
		nuestraTextura = vec2(aTexCoord.x, aTexCoord.y);
}