#include "plain.h"
#include <InitShader.h>

void Plain::append_square(Vertex a, Vertex b, Vertex c, Vertex d)
{
	this->vertices.push_back(a);
	this->vertices.push_back(b);
	this->vertices.push_back(c);
	this->vertices.push_back(a);
	this->vertices.push_back(c);
	this->vertices.push_back(d);
}

void Plain::printDivInfo()
{
	std::cout << "division: " << div << ", Num of Triangles: " << n_triangles << ", Num of Vertices: " << n_vertices << std::endl;
}

void Plain::modifyDiv(int delta)
{
	if (delta < 0 && div > 2)
		div -= 1;
	else if (delta > 0)
		div += 1;
	n_triangles = div * div * 2;
	n_vertices = n_triangles * 3;
}

void Plain::modifyRot(vec3 dAngle)
{
	rot += dAngle;
	//0.0 <= rot < 360.0
	if (rot.x < 0)
		rot.x += 360.0f;
	else if (rot.x >= 360)
		rot.x -= 360.0f;

	if (rot.y < 0)
		rot.y += 360.0f;
	else if (rot.y >= 360)
		rot.y -= 360.0f;

	if (rot.z < 0)
		rot.z += 360.0f;
	else if (rot.z >= 360)
		rot.z -= 360.0f;
}

void Plain::initBuffers()
{
	//VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//init VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), nullptr, GL_DYNAMIC_DRAW);

	//load shaders & activate shader program
	program = InitShader("vshader_plain.glsl", "fshader_plain.glsl");
	glUseProgram(program);

	//set stride
	GLsizei stride = sizeof(Vertex);
	//first attribute
	GLuint vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, stride, BUFFER_OFFSET(0));
	//second attribute
	GLuint vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, stride, BUFFER_OFFSET(sizeof(vec4)));

	glBindVertexArray(0);
}

void Plain::updateBuffers()
{
	vertices.clear();

	float min = -size / 2.0f;
	float max = size / 2.0f;
	float ds = (max - min) / div;

	vec4 baseColor = vec4(0.5f, 0.5f, 0.5f, 1.0f);
	for (int i = 0; i < div; i++)
	{
		for (int j = 0; j < div; j++)
		{
			float x0 = min + i * ds;
			float y0 = min + j * ds;

			float dColor = 0.2f;
			int p = (i + j) % 2; //0 or 1
			vec4 color = baseColor + p * vec4(dColor, dColor, dColor, 0.0f);

			Vertex a = { vec4(x0 + ds,	y0 + ds,	0.0f, 1.0f), color };
			Vertex b = { vec4(x0,		y0 + ds,	0.0f, 1.0f), color };
			Vertex c = { vec4(x0,		y0,			0.0f, 1.0f), color };
			Vertex d = { vec4(x0 + ds,	y0,			0.0f, 1.0f), color };

			append_square(a, b, c, d);
		}
	}

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_DYNAMIC_DRAW);
}

void Plain::draw()
{
	glUseProgram(program);

	GLuint u_time = glGetUniformLocation(program, "u_time");
	glUniform1f(u_time, g_time);

	GLint plain_size = glGetUniformLocation(program, "plain_size");
	glUniform1f(plain_size, plain.size);

	int plain_wave = glGetUniformLocation(program, "plain_wave");
	glUniform1i(plain_wave, plain.wave);

	glm::mat4 modelMatrix = buildRotMatrix(rot);
	GLint u_model = glGetUniformLocation(program, "u_model");
	glUniformMatrix4fv(u_model, 1, GL_FALSE, &modelMatrix[0][0]);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}