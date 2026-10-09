#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 model;
// uniform mat4 projection;
uniform mat4 nagativeZ; // 지금은 NDC좌표사용중이라 z부호만 바꿔줌

void main()
{
    gl_Position = nagativeZ * model * vec4(aPos, 1.0);
}