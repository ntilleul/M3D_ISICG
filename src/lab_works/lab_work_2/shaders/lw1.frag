#version 450
in vec4 vColor;
layout( location = 0) out vec4 FragmentColor;
void main() {
	FragmentColor = vColor;
}
