#version 330 core

out vec4 FragColor;
in vec3 pos;
in float uTime;
in vec2 uMouse;
in float maxx;
in float maxy;
in float miny;
in float minx;

vec3 palette(float t)
{

	vec3 a = vec3(0.5,0.5,0.5);
	vec3 b = vec3(0.5,0.5,0.5);
	vec3 c = vec3(1.0,1.0,1.0);
	vec3 d = vec3(0.263, 0.416,0.557);

	return a + b*cos(6.28318*(c*t+d));
}

float iterateMandelBrot(vec2 coord)
{
	float x = 0.f;
	float y = 0.f;

	for(float i = 1.0; i < 1000; i++)
	{
		if (x*x + y*y > 4.0)
		{
			return i / 1000;
		}
		float xtemp = x*x - y*y + coord.x;
		y = 2.0 * x * y + coord.y;
		x = xtemp;
	}
	return 1.0;
}

void main()
{
	float x = ((maxx - minx) * pos.x) + minx;
	float y = ((maxy - miny) * pos.y) + miny;

	float i = iterateMandelBrot(vec2(x,y));

	FragColor = vec4(i,i,i,1.0);

}

