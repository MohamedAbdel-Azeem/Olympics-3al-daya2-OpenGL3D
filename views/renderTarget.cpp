#include <glut.h>
#include "../Headers/views/renderTarget.h"

void renderTarget() {
	glPushMatrix();
	glColor3f(0, 1, 0);
	glutSolidCube(1);
	glPopMatrix();
}