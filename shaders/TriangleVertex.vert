#version 330 core
layout (location = 0) in vec3 aPos;
uniform float uTime;
out vec4 Pos;
out vec4 color;
void main()
{
	float v = sin(uTime);
	float y = cos(uTime);
	gl_Position = vec4(aPos , 1.0 );
	Pos = vec4(aPos , 1.0);
	color = vec4(v,y,v,1.f);
}
