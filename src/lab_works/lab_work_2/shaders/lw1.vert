#version 450
layout( location = 0 ) in vec2 VertexPosition;
layout(location = 1) in vec3 VertexColor;

out vec4 vColor;

uniform float uTranslationX;

void main() {
	gl_Position = vec4(VertexPosition.x + uTranslationX, VertexPosition.y, 0, 1.0);
	vColor = vec4(VertexColor, 1.f);
}
