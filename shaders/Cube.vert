#version 330 core
layout(location = 0) in vec3 aPos;

void main() {
    // Adjust x by aspect ratio to keep it square
    gl_Position = vec4(aPos.x / aspect, aPos.y, aPos.z, 1.0);
}
