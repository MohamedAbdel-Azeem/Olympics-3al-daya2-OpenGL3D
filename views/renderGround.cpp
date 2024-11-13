#include <glut.h>
#include "Headers/views/renderGround.h"

void renderGround() {
	glPushMatrix();
	glColor3f(0, 0.3, 0);
	glScalef(5, 0.1, 5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.05, 0.05, 0.05);
	glTranslatef(0,0.05, 0.9);
	glScalef(3, 0.1, 0.1);
	glutSolidCube(1);
	glPopMatrix();

}