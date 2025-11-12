#include "util.h"

void printIntro()
{
	std::cout << "A Waving Color Plain" << std::endl;
	std::cout << "Programming Assignment #1 for Computer Graphics" << std::endl;
	std::cout << "Department of Software, Sejong University" << std::endl;
	std::cout << "21011650 Kyumin Lee" << std::endl << std::endl;
	std::cout << "----------------------------------------------------------------" << std::endl;
	std::cout << "`1' key: Decrease the number of division" << std::endl;
	std::cout << "`2' key: Increase the number of division" << std::endl;
	std::cout << "`w' key: Show/Hide wave" << std::endl;
	std::cout << "Spacebar: Start/Stop rotating and waving" << std::endl;
	std::cout << "Mouse Drag: Rotate plane" << std::endl;
	std::cout << "Mouse Scroll: Zoom in/out" << std::endl;
	std::cout << "`q' Key: Exit program." << std::endl;
	std::cout << "----------------------------------------------------------------" << std::endl << std::endl;
}

glm::mat4 buildRotMatrix(vec3 rot)
{
	vec3 rad = { glm::radians(rot.x), glm::radians(rot.y), glm::radians(rot.z) };

	glm::mat4 Rx(1.0f);
	Rx[1][1] = cos(rad.x);  Rx[2][1] = -sin(rad.x);
	Rx[1][2] = sin(rad.x);  Rx[2][2] = cos(rad.x);
	glm::mat4 Ry(1.0f);
	Ry[0][0] = cos(rad.y);  Ry[2][0] = sin(rad.y);
	Ry[0][2] = -sin(rad.y); Ry[2][2] = cos(rad.y);
	glm::mat4 Rz(1.0f);
	Rz[0][0] = cos(rad.z);  Rz[1][0] = -sin(rad.z);
	Rz[0][1] = sin(rad.z);  Rz[1][1] = cos(rad.z);

	return Rx * Ry * Rz;
}