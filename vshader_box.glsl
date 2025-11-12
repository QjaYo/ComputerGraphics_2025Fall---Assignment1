#version 330 core
layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vColor;

out vec4 fColor;

uniform float u_time;
uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;

void main()
{
    vec4 pos = vPosition;

    gl_Position = u_proj * u_view * u_model * pos;
    fColor = vColor;
}

