#version 330 core

in vec2 pos;
out vec4 FragColor;
void main()
{
	FragColor = vec4(pos.x,0.0, 0.0, 1.0);
}
