#pragma once

#include <vgl.h>
#include <glm/glm.hpp>
#include <vec.h>
#include <vector>

struct Vertex
{
	vec4 pos;
	vec4 color;
};

class Plain;
class Box;

//screen
extern const unsigned int SCR_WIDTH;
extern const unsigned int SCR_HEIGHT;

extern GLuint program;

//object
extern Plain plain;
extern Box box;

//constant
extern const float PI;

//camera
extern float f_len;
extern float px, py;
extern float zoom;

//state
extern float g_time;
extern bool mouse_leftButton;
extern vec2 mouse_last;