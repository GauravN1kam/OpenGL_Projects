#version 330 core

out vec4 FragColor;
in vec3 pos;
in float uTime;

void main()
{
		vec2 p = pos.xy - 0.5;
		float k = sin(uTime) * 0.5 + 0.5;
		float radius = 0.5;

		float d = length(p) -0.5;
		d = abs(d);

		d = smoothstep(0.0, 0.1, d);

		vec3 color = vec3(d);
    
    FragColor = vec4(color, 1.0);
}
