#version 330 core
layout(location = 0) in vec3 aPos;
uniform float aspect;
uniform float u_Time;

out vec3 pos;
out float uTime;
void main() {
    // Adjust x by aspect ratio to keep it square
    gl_Position = vec4(aPos.x / aspect, aPos.y, aPos.z, 1.0);
		pos = aPos + 0.5;
		uTime = u_Time;
}
