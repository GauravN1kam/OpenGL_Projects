#version 330 core
layout(location = 0) in vec3 aPos;
uniform float aspect;
uniform float u_Time;
uniform vec2 u_Mouse;

out vec3 pos;
out float uTime;
out vec2 uMouse;
void main() {
    // Adjust x by aspect ratio to keep it square
    gl_Position = vec4(aPos.x / aspect, aPos.y, aPos.z, 1.0);
		pos = aPos + 0.5;
		uTime = u_Time;
		uMouse = u_Mouse;
}
