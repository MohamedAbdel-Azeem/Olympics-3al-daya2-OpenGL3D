#include "Headers/views/renderWall.h"
#include <glut.h>

void renderWall(float x, float y, float z , bool rotate) {
	glPushMatrix();
	glColor3f(0.5,0.5 , 0.5);
	if (rotate) {
		glScalef(5, 1, 0.2);
	}
	else {
		glScalef(0.2, 1, 5);
	}
	glTranslatef(x, y, z);
	glutSolidCube(1);
	glPopMatrix();
}