#version 330 core
in vec4 Pos;
out vec4 FragColor;
void main()
{
	FragColor = vec4(Pos.xy, 0.f , 1.0f);	
}
