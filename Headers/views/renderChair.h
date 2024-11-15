#pragma once
#ifndef RENDER_CHAIR_H
#define RENDER_CHAIR_H

#include <cmath>
#include <glut.h>

void renderChair(float posX, float posY, float posZ, bool animate) {
	static float zOffset = 0;
	if (animate) {
		zOffset = sin(glutGet(GLUT_ELAPSED_TIME) * 0.001) * 0.3;
	}
	else {
		zOffset = 0;
	}

	glPushMatrix();
	glTranslatef(posX, posY, posZ+zOffset);
	glScalef(0.5, 0.5, 0.5);
	glRotatef(180, 0, 1, 0);

	glColor3f(0.9, 0.6, 0.1);

	//chair base
	glPushMatrix();
	glTranslatef(0, 0.7, 0);
	glScalef(0.5, 0.15, 0.5);
	glutSolidCube(1);
	glPopMatrix();

	//chair back
	glPushMatrix();
	glTranslatef(0, 1.4, -0.25);
	glScalef(0.5, 0.5, 0.05);
	glutSolidCube(1);
	glPopMatrix();





	glColor3f(0, 0, 0);

	glPushMatrix();
	glTranslatef(-0.2, 1, -0.25);
	glScalef(0.05, 0.5, 0.03);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.2, 1, -0.25);
	glScalef(0.05, 0.5, 0.03);
	glutSolidCube(1);
	glPopMatrix();


	//chair legs
	glPushMatrix();
	glTranslatef(0.25, 0.35, 0.2);
	glScalef(0.05, 0.7, 0.05);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.25, 0.35, 0.2);
	glScalef(0.05, 0.7, 0.05);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.25, 0.35, -0.2);
	glScalef(0.05, 0.7, 0.05);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.25, 0.35, -0.2);
	glScalef(0.05, 0.7, 0.05);
	glutSolidCube(1);
	glPopMatrix();

	glPopMatrix();


}


#endif

