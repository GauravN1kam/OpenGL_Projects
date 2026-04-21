#version 330 core
out vec4 FragColor;
in vec4 pos;

vec3 palette(float t)
{

	vec3 a = vec3(0.5,0.5,0.5);
	vec3 b = vec3(0.5,0.5,0.5);
	vec3 c = vec3(1.0,1.0,1.0);
	vec3 d = vec3(0.263, 0.146,0.557);

	return a + b*cos(6.28318*(c*t+d));
}

void main() {

    FragColor = vec4(0.4f,pos.x,pos.y, pos.z);
}

