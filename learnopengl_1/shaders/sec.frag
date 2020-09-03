#version 330 core
out vec4 FragColor;

uniform float time;

void main()
{
    FragColor = vec4(sin(time) * 4, 0.3f, 1.0f, 1.0f);
}