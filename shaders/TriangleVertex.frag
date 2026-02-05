#version 330 core
in vec4 Pos;
in vec4 color;
out vec4 FragColor;
void main()
{
	vec4 k = color;
	FragColor = Pos;	
}
