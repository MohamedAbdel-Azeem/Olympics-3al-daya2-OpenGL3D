#include "Headers/views/renderFence.h"
#include <cmath>
#include <glut.h>

void renderFence(float x, float y, float zStart , float zEnd) {
	for (float z = zStart; z < zEnd; z += 0.5) {
		glPushMatrix();
		glTranslatef(x, y, z);
		glScalef(0.5f, 0.5f, 0.5f); // Scale down the fence
		// Fence (Cylinder)
		glColor3f(0.1, 0.1, 0.1);
		glPushMatrix();
		glTranslatef(0.0f, 0.5f, 0.0f);  // Position the fence below the head
		glRotatef(90, 1.0f, 0.0f, 0.0f); // Rotate to align with Y-axis
		GLUquadric* fence = gluNewQuadric();
		gluCylinder(fence, 0.05, 0.05, 1, 20, 20);  // Radius 0.05, height 0.8
		gluDeleteQuadric(fence);
		glPopMatrix();
		glPopMatrix();  // Restore the previous transformation matrix
	}



	glPushMatrix();
	glTranslatef(x, y, zStart);
	glScalef(0.5f, 0.5f, 0.9f); // Scale down the fence
	// Fence (Cylinder)
	glColor3f(0.1, 0.1, 0.1);
	glPushMatrix();
	glTranslatef(0.0f, 0.5f, 0.0f);  // Position the fence below the head
	glRotatef(90, 0.0f, 0.0f, 1.0f); // Rotate to align with Y-axis
	GLUquadric* fence = gluNewQuadric();
	gluCylinder(fence, 0.05, 0.05, abs(zEnd)+abs(zStart), 20, 20);  // Radius 0.05, height 0.8
	gluDeleteQuadric(fence);
	glPopMatrix();
	glPopMatrix();  // Restore the previous transformation matrix

	glPushMatrix();
	glColor3f(0.1, 0.1, 0.1);
	glTranslatef(x, y+0.3, zEnd-0.5);
	glScaled(0.5, 0.5, 0.5);
	glutSolidSphere(0.1, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.1, 0.1, 0.1);
	glTranslatef(x, y+0.3, zStart);
	glScaled(0.5, 0.5, 0.5);
	glutSolidSphere(0.1, 20, 20);
	glPopMatrix();

}
