#version 330 core
layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vColor;

out vec4 fColor;
out float fHeight;

uniform float u_time;
uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;

uniform float plain_size;
uniform bool plain_wave;
uniform bool plain_active;

void main()
{
    vec4 pos = vPosition;

    //wave
    if (plain_wave)
    {
        float amp = 0.4;
        float PI = 3.1415926;
        float freq = 1.3;
        float wavenumber = 30.0;
    
        float dist = length(vec3(vPosition.x, vPosition.y, 0));
        float damping = exp(-5.0 * dist);
        float dh = amp * sin((2*PI*freq)*u_time - wavenumber*dist) * damping;
        //float dh = amp * sin(2*PI*freq * u_time) * damping; //no phase difference
        pos.z += dh;

        //pass attributes to fshader
        float normalizedHeight = dh / amp;
        fHeight = normalizedHeight; //range(-1.0~1.0)
    }
    else
    {
        fHeight = 0.0;
    }

    gl_Position = u_proj * u_view * u_model * pos;
    fColor = vColor;
}

