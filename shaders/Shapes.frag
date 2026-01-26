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

void main()
{
		vec2 p = pos.xy - 0.5;
		vec2 p0 = p;
		vec3 finalColor = vec3(0.0);
		for(float i = 0.0; i < 6.0; i++)
		{
			p = fract(p * 1.5) - 0.5;

			float d = length(p) * exp(-length(p0));


			vec3 color = palette(length(p0) + i*.4 + uTime*0.4);
			d = sin(d*8. + uTime)/8.;
			d = abs(d);

			d = pow(0.01/d, 3.0);
			color *= d;
			finalColor += color;
		}
		
    FragColor = vec4(finalColor, 1.0);
}
