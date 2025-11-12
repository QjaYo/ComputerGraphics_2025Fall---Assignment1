#pragma once

#include "global.h"
#include "util.h"

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case ' ':
	{
		plain.active = !plain.active;
		glutPostRedisplay();
		break;
	}
	case 'w':
	{
		plain.wave = !plain.wave;
		glutPostRedisplay();
		break;
	}
	case '1':
	{
		plain.modifyDiv(-1);
		plain.printDivInfo();
		plain.updateBuffers();
		break;
	}
	case '2':
	{
		plain.modifyDiv(+1);
		plain.printDivInfo();
		plain.updateBuffers();
		break;
	}
	case 'q':
		exit(0);
		break;
	}
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		mouse_leftButton = true;
		mouse_last = vec2(x, y);
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		mouse_leftButton = false;
	}
}

void motion(int x, int y)
{
	if (mouse_leftButton)
	{
		float dx = float(x - mouse_last.x);
		float dy = float(y - mouse_last.y);

		//해결못함: 평면이 거꾸로 뒤집혔을때 거꾸로 회전함
		glm::vec4 normal = buildRotMatrix(plain.rot) * glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
		if (normal.y >= 0)
			plain.modifyRot(vec3{ -dy, 0.0f, -dx });
		else
			plain.modifyRot(vec3{ -dy, 0.0f, +dx });

		mouse_last = vec2(x, y);

		glutPostRedisplay();
	}
}

void mouseWheel(int whell, int direction, int x, int y)
{
	float sensitivity = 0.01f;
	static const float f_len_min = 0.5f;
	static const float f_len_max = 2.0f;
	if (direction > 0 && f_len >= f_len_min)	f_len -= sensitivity;
	if (direction < 0 && f_len <= f_len_max)	f_len += sensitivity;
	glutPostRedisplay();
}

void idle()
{
	static int last = glutGet(GLUT_ELAPSED_TIME);  //(program start ~ last) [msec]
	int now = glutGet(GLUT_ELAPSED_TIME); //(program start ~ now) [msec]
	float dt = (now - last) / 1000.0f;	//(last ~ now) [sec]
	last = now;

	if (plain.active)
	{
		plain.modifyRot(vec3{ 0.0f, 0.0f, plain.angSpeed * dt });

		g_time += dt;
	}
	glutPostRedisplay();
}

void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(program);

	//update uniforms
	glm::mat4 viewMatrix = glm::mat4(1.0f);
	GLint u_view = glGetUniformLocation(program, "u_view");
	glUniformMatrix4fv(u_view, 1, GL_FALSE, &viewMatrix[0][0]);

	glm::mat4 projMatrix =
	{
		f_len,	0,		0,		0,
		0,		f_len,	0,		0,
		px,		py,		1,		0,
		0,		0,		0,		1
	};
	GLint u_proj = glGetUniformLocation(program, "u_proj");
	glUniformMatrix4fv(u_proj, 1, GL_FALSE, &projMatrix[0][0]);

	plain.draw();
	//box.draw();

	glutSwapBuffers();
}