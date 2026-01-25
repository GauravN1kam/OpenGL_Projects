#version 330 core
layout(location = 0) in vec3 aPosition;
in vec3 aTexCord;
out vec2 pos;
void main()
{
	pos = aTexCord.xy;
	vec4 Position = vec4(aPosition, 1.0);
	Position.xy = Position.xy * 2.0 - 1.0;

	gl_Position = Position;
}
