#include <cmath>
#include <glut.h>
#include "../Headers/views/renderTarget.h"

void renderTarget(float posX, float posY, float posZ) {

	GLdouble clipPlane[] = { 0.0, 0.0, 1.0, 0.0 };

	static float offsetY = 0;
	static float offsetX = 0;
	offsetY = sin(glutGet(GLUT_ELAPSED_TIME) * 0.001) * 0.1;
	offsetX = cos(glutGet(GLUT_ELAPSED_TIME) * 0.001) * 0.1;


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
	glScalef(0.6, 0.6, 0.005);
	glutSolidCube(1);
	glPopMatrix();

	// Target Paper First Circle (Sphere)
	glPushMatrix();
	glClipPlane(GL_CLIP_PLANE0, clipPlane);
	glEnable(GL_CLIP_PLANE0);
	glColor3f(1, 0.9, 0);
	glTranslatef(0 + offsetX, 0.92 + offsetY, 0);
	glutSolidSphere(0.15, 20, 20);
	glDisable(GL_CLIP_PLANE0);
	glPopMatrix();

	// Target Paper Second Circle (Sphere)
	glPushMatrix();
	glClipPlane(GL_CLIP_PLANE0, clipPlane);
	glEnable(GL_CLIP_PLANE0);
	glColor3f(1,0, 0);
	glTranslatef(0 + offsetX, 0.92 + offsetY, 0.07);
	glutSolidSphere(0.1, 20, 20);
	glDisable(GL_CLIP_PLANE0);
	glPopMatrix();


	glPopMatrix();
}