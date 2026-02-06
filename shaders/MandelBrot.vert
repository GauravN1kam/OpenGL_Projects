#version 330 core
layout(location = 0) in vec3 aPos;
uniform float aspect;
uniform float u_Time;
uniform vec2 u_Mouse;
uniform float Maxx;
uniform float Maxy;
uniform float Miny;
uniform float Minx;

out vec3 pos;
out float uTime;
out vec2 uMouse;
out float maxx;
out float maxy;
out float miny;
out float minx;

void main() {
    // Adjust x by aspect ratio to keep it square
		pos = aPos + 0.5;
		uTime = u_Time;
		uMouse = u_Mouse;
		maxx = Maxx;
		maxy = Maxy;
		miny = Miny;
		minx = Minx;

    gl_Position = vec4(aPos.x / aspect, aPos.y, aPos.z, 1.0);
}
