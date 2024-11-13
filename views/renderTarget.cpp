#include <glut.h>
#include "../Headers/views/renderTarget.h"

void renderTarget(float posX, float posY, float posZ) {

	glPushMatrix();

	glTranslatef(posX, posY, posZ);


	//first level (first Cube)
	glPushMatrix();
	glColor3f(0.4, 0.3, 0.5);
	glScalef(1.5, 0.3, 0.7);
	glutSolidCube(1);
	glPopMatrix();


	//second level (second Cube)
	glPushMatrix();
	glColor3f(0.4, 0.3, 0.5);
	glTranslatef(0, 0.2, 0);
	glScalef(1, 0.3, 0.5);
	glutSolidCube(1);
	glPopMatrix();


	// Pole/Stick
	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslatef(0, 0.4, 0);
	glScalef(0.1, 0.7, 0.1);
	glutSolidCube(1);
	glPopMatrix();


	// Target Paper
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(0, 0.9, 0);
	glScalef(0.4, 0.4, 0.005);
	glutSolidCube(1);
	glPopMatrix();

	glPopMatrix();
}