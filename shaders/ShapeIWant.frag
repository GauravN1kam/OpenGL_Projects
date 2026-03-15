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

vec3 circle(vec2 p)
{
	if((p.x * p.x) + (p.y * p.y) >= 0.009 && (p.x * p.x) + (p.y * p.y) <= 0.01)
	{
		return vec3(0.02, 0.01, 0.55);
	}
	else{
		return vec3(1,1,1);
	}
}

void main()
{
		vec2 p = pos.xy - 0.5;
		vec3 color = vec3(0,0,0);
		if(p.y >= -0.3 && p.y <= -0.1 && p.x >= -0.4 && p.x <= 0.4)
		{
			color = vec3 (0.016, 0.416, 0.220) ;
		}
		else if(p.y > -0.1 && p.y <= 0.1 && p.x >= -0.4 && p.x <= 0.4)
		{
			color = circle(p);
		}
		else if(p.y > 0.1 && p.y <= 0.3 &&p.x >= -0.4 && p.x <= 0.4)
		{
				color = vec3(1, 0.4, 0.12);
		}

	
    FragColor = vec4(color,1.0);
}
