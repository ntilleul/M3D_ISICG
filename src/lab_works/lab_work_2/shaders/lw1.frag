#version 450
in vec4 vColor;
layout( location = 0) out vec4 FragmentColor;

uniform float uLight=1.f;

void main() {
	FragmentColor = vColor * uLight;
}
