#include <glut.h>
#include "Headers/views/renderGround.h"

void renderGround() {
	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glScalef(5, 0.1, 5);
	glutSolidCube(1);
	glPopMatrix();
}