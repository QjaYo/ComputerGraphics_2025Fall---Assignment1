#include "global.h"
#include "plain.h"
#include "box.h"
#include "util.h"
#include "callback.h"

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(SCR_WIDTH, SCR_HEIGHT);
	glutCreateWindow("Waving Plain");

	glewExperimental = GL_TRUE;
	glewInit();

	glEnable(GL_DEPTH_TEST);

	plain.initBuffers();
	plain.updateBuffers();
	//box.initBuffers();
	//box.updateBuffers();

	printIntro();
	plain.printDivInfo();

	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutMouseWheelFunc(mouseWheel);

	glutMainLoop();

	return 0;
}