#pragma once
#ifndef RENDERBULLET_H
#define RENDERBULLET_H
#include <cmath>
#include <glut.h>

void renderBullet(float posX, float posY, float posZ, bool animate , bool bulletCollected) {
	if (bulletCollected) {
		return;
	}

	static float gunRotAngle = 0;
	if (animate) {
		gunRotAngle = abs(cos(glutGet(GLUT_ELAPSED_TIME) * 0.001) * 90);
	}
	else {
		gunRotAngle = 0;
	}

	glPushMatrix();
	glTranslatef(posX, posY , posZ);
	glRotatef(-90+gunRotAngle, 1, 0, 0);
	glScalef(0.25,0.7,0.25);


	glColor3f(0, 0, 0);
	// base
	glPushMatrix();
	glTranslatef(0, 0.2, 0);
	glScalef(0.25, 0.05, 0.25);
	glutSolidCube(1);
	glPopMatrix();

	glColor3f(1, 0.84, 0);
	// Cylinder indicating bullet body
	glPushMatrix();
	glTranslatef(0, 0.2, 0);
	glScalef(0.1, 0.2, 0.1);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(gluNewQuadric(), 1, 1, 1, 10, 10);
	glPopMatrix();

	// Cone indicating Bullet head
	glPushMatrix();
	glTranslatef(0, 0.4, 0);
	glScalef(0.1, 0.1, 0.1);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(gluNewQuadric(), 1, 0, 1, 10, 10);
	glPopMatrix();

	glPopMatrix();

}


#endif // !RENDERBULLET_H