#version 330 core

out vec4 FragColor;
in vec3 pos;
in float uTime;
in vec2 uMouse;

float sdSphere(vec3 sphere, float s)
{
	return length(sphere) - s;
}

float sdBox(vec3 point, vec3 box)
{
	vec3 q = abs(point) - box;
	return length(max(q, 0.0)) + min(max(q.x, max(q.y, q.z)), 0.0);
}

float smin(float a, float b, float k)
{
	float h = max(k - abs(a - b), 0.0) / k;
	return min(a,b) - h*h*h*k*(1.0/6.0);
}


mat2 rot2D(float a)
{
    float s = sin(a);
    float c = cos(a);

    return mat2(
        c, -s,
        s,  c
    );
}

float sdOctaHedran(vec3 p, float s)
{
	p = abs(p);

	return (p.x + p.y + p.z - s) * 0.57735027;
}

float map(vec3 point)
{
	point.z += uTime * 0.4;

	point.xy = (fract(point.xy) - 0.5);
	point.z = mod(point.z, 0.25) - 0.125;


	// point.xy *= rot2D(uTime) ;

	float box = sdOctaHedran(point, 0.15);



	return box;
}

vec3 palette(float t)
{

	vec3 a = vec3(0.5,0.5,0.5);
	vec3 b = vec3(0.5,0.5,0.5);
	vec3 c = vec3(1.0,1.0,1.0);
	vec3 d = vec3(0.263, 0.416,0.557);

	return a + b*cos(6.28318*(c*t+d));
}

void main()
{
		vec2 uv = pos.xy - 0.5;

		//initializaztion process
		vec3 ray_origin = vec3(0,0,-3);
		vec3 ray_direction = normalize(vec3(uv,1)); 
		vec3 col = vec3(0.0);
		float t = 0.0f; //distance traveled;
		// ray_origin.yz *= rot2D(uMouse.y);
		// ray_direction.yz *= rot2D(uMouse.y);
		// ray_origin.xz *= rot2D(-uMouse.x);
		// ray_direction.xz *= rot2D(-uMouse.x);

		// RayMarching
		int i;
		for(i = 0; i < 80; i++)
		{
			vec3 p = ray_origin + ray_direction * t;
			p.xy *= rot2D(t*0.2 * uMouse.x);

			p.y += sin(t * (uMouse.y+1.) * 0.5) * 0.35;

			float d = map(p);
			t += d;

			if(d < 0.001 || d > 100.) break;

		}

		col = palette(t * 0.04 + float(i) * 0.005);
    FragColor = vec4(col, 1.0);
}

