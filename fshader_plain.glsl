#version 330 core

in vec4 fColor;
in float fHeight; //range(-1.0~1.0)

out vec4 FragColor;

void main()
{
    vec4 lowColor = vec4(0.0, 0.5, 1.0, 1.0);   //blue    
    vec4 highColor = vec4(1.0, 0.5, 0.0, 1.0);  //orange

    float factor = clamp(2.0*abs(fHeight), 0.0, 1.0);
    if (fHeight > 0.0)
        FragColor = mix(fColor, highColor, factor);
    else
        FragColor = mix(fColor, lowColor, factor);
}