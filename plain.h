#pragma once

#include "global.h"
#include "util.h"

class Plain
{
public:
	GLuint VAO = 0, VBO = 0;
	std::vector<Vertex> vertices;

	int div = 30;
	int n_triangles = div * div * 2;
	int n_vertices = n_triangles * 3;
	vec3 center = { 0.0f, 0.0f, 0.0f };
	float size = 1.4f;
	vec3 rot = { 220.0f, 0.0f, 20.0f };
	bool wave = false;
	bool active = false;
	float angSpeed = 30.0f;		//degree per sec

	void append_square(Vertex a, Vertex b, Vertex c, Vertex d);
	void printDivInfo();
	void modifyDiv(int delta);
	void modifyRot(vec3 dAngle);
	void initBuffers();
	void updateBuffers();
	void draw();
};