#pragma once
#ifndef RENDERLASER_H
#define RENDERLASER_H
#include <glut.h>

void renderLaser(float posX, float posY, float posZ) {
	
	const float offsetY = 0.45f;
	const float offsetZ = - 2.5f;
	
	glPushMatrix();
	glColor3f(0, 1, 0);
	glTranslatef(posX, posY + offsetY, posZ + offsetZ);
	glScalef(0.01, 0.01, 4);
	glutSolidCube(1);
	glPopMatrix();
}


#endif