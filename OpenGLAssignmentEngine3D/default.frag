#version 330 core
in vec3 VertColor;
out vec4 FragColor;

uniform vec3 color = vec3(1.0, 1.0, 1.0);
uniform float transparency = 1.0;

void main()
{
    FragColor = vec4(VertColor * color, transparency);
}