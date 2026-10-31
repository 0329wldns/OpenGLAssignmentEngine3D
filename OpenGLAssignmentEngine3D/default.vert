#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 VertColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 ortho;
uniform mat4 perspective;
uniform bool projectionMode;    // true: perspective, false: orthographic


void main()
{
    if (projectionMode) gl_Position = perspective * view * model * vec4(aPos, 1.0);
    else gl_Position = ortho * view * model * vec4(aPos, 1.0);
    VertColor = aColor;
}