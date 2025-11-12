#include "global.h"
#include "plain.h"
#include "box.h"
#include <vector>

//screen
const unsigned int SCR_WIDTH = 512;
const unsigned int SCR_HEIGHT = 512;

//object
Plain plain;
//Box box(vec3{ 0.4f, 0.4f, 0.4f }, vec3{ 0.1f, 0.1f, 0.1f }, vec4{ 0.5f, 0.1f, 0.5f });

//OpenGL
GLuint program;

//constant
const float PI = 3.141592f;

//camera
float f_len = 1.0f;
float px = 0, py = 0;
float zoom = 1.0f;

//state
float g_time = 0.0f;
bool mouse_leftButton = false;
vec2 mouse_last;