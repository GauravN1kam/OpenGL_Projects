#version 330 core

out vec4 FragColor;
in vec3 pos;
in float uTime;

vec3 palette(float t)
{

	vec3 a = vec3(0.5,0.5,0.5);
	vec3 b = vec3(0.5,0.5,0.5);
	vec3 c = vec3(1.0,1.0,1.0);
	vec3 d = vec3(0.263, 0.146,0.557);

	return a + b*cos(6.28318*(c*t+d));
}

float square(vec2 p)
{
	if(p.x >=-0.5 && p.x <= 0.5 && p.y <= 0.5 && p.y >= -0.5)
	{
		return 1.0f;
	}
	else{
		return 0.0f;
	}

}

void main()
{
		vec2 p = pos.xy - 0.5;
		float k = square(p);
	
    FragColor = vec4(k,k,k,1.0);
}
