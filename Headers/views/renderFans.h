#pragma once
#ifndef RENDERFANS_H
#define RENDERFANS_H
#include <vector>
#include <cstdlib> // For rand()
#include <glut.h>



struct color {
	float r, g, b;
};

color shirtColors[] = {
	{1, 0, 0},
	{0, 0, 1},
	{0, 1, 0}
};

color pantsColors[] = {
	{0.6f, 0.5f, 0.3f},
	{0.5f, 0.8f, 0.3f}
};

struct Fan {
	color shirtColor;
	color pantColor;
	float posX, posY, posZ, rotY;
};

std::vector<Fan> fans;

void renderFan(float posX, float posY, float posZ , float rotY, color shirtColor, color pantColor) {
	
	
	glPushMatrix();
	glTranslatef(posX, posY, posZ);

	glScalef(0.5f, 0.5f, 0.5f); // Scale down the player
	glRotatef(90, 0, rotY, 0); // Rotate to face the camera

	glColor3f(0.8f, 0.5f, 0.3f);
	// Head (Sphere)
	glPushMatrix();
	glTranslatef(0.0f, 0.7f, 0.0f);  // Position the head above the body
	glutSolidSphere(0.2, 20, 20);    // Radius 0.2, 20 slices, 20 stacks
	glPopMatrix();

	glColor3f(shirtColor.r, shirtColor.g, shirtColor.b);
	// Body (Cylinder)
	glPushMatrix();
	glTranslatef(0.0f, 0.5f, 0.0f);  // Position the body below the head
	glRotatef(90, 1.0f, 0.0f, 0.0f); // Rotate to align with Y-axis
	GLUquadric* body = gluNewQuadric();
	gluCylinder(body, 0.25, 0.15, 0.8, 20, 20);  // Radius 0.15, height 0.8
	gluDeleteQuadric(body);
	glPopMatrix();

	glColor3f(0.8f, 0.5f, 0.3f);

	// Left Arm (Cylinder, holding the gun)
	glPushMatrix();
	glTranslatef(-0.25f, 0.4f, 0); // Position left arm to the side of body and angled for holding
	glRotatef(-80, 1.0f, 0.0f, -0.7f);  // Rotate to align for holding position
	GLUquadric* leftArm = gluNewQuadric();
	gluCylinder(leftArm, 0.05, 0.05, 0.5, 10, 10); // Radius 0.05, height 0.5
	gluDeleteQuadric(leftArm);
	glPopMatrix();

	// Right Arm (Cylinder, holding the gun)
	glPushMatrix();
	glTranslatef(0.25f, 0.4f, 0); // Position right arm to the side of body and angled for holding
	glRotatef(-80, 0.0f, -1.0f, -0.9f); // Rotate to align for holding position
	GLUquadric* rightArm = gluNewQuadric();
	gluCylinder(rightArm, 0.05, 0.05, 0.5, 10, 10); // Radius 0.05, height 0.5
	gluDeleteQuadric(rightArm);
	glPopMatrix();

	// Legs
	glColor3f(pantColor.r, pantColor.g, pantColor.b);

	// Left Leg (Cylinder)
	glPushMatrix();
	glTranslatef(-0.1f, -0.3f, 0.0f); // Position left leg below the body
	glRotatef(90, 1.0f, 0.0f, 0.0f);  // Rotate to align with Y-axis
	GLUquadric* leftLeg = gluNewQuadric();
	gluCylinder(leftLeg, 0.05, 0.05, 0.6, 10, 10); // Radius 0.05, height 0.6
	gluDeleteQuadric(leftLeg);
	glPopMatrix();

	// Right Leg (Cylinder)
	glPushMatrix();
	glTranslatef(0.1f, -0.3f, 0.0f); // Position right leg below the body
	glRotatef(90, 1.0f, 0.0f, 0.0f); // Rotate to align with Y-axis
	GLUquadric* rightLeg = gluNewQuadric();
	gluCylinder(rightLeg, 0.05, 0.05, 0.6, 10, 10); // Radius 0.05, height 0.6
	gluDeleteQuadric(rightLeg);
	glPopMatrix();

	glPopMatrix();
}

void initializeFans(float posStartZ, float posX, bool isAnimating, float rotY) {
	float posZ = posStartZ;
	float posZIncrement = 1.0f;
	int numShirtColors = sizeof(shirtColors) / sizeof(shirtColors[0]);
	int numPantColors = sizeof(pantsColors) / sizeof(pantsColors[0]);

	for (int i = 0; i < 4; i++) {
		color shirtColor = shirtColors[rand() % numShirtColors];
		color pantColor = pantsColors[rand() % numPantColors];
		fans.push_back({ shirtColor, pantColor, posX, 0.5f, posZ, rotY });
		posZ += posZIncrement;
	}
}

void renderFans(bool isAnimating) {

	static float offsetY = 0.0f;
	if (isAnimating) {
		offsetY = sin(glutGet(GLUT_ELAPSED_TIME) * 0.01f) * 0.1f;
	}
	else {
		offsetY = 0.0f;
	}
	

	for (Fan fan : fans) {
		renderFan(fan.posX, fan.posY + offsetY, fan.posZ, fan.rotY, fan.shirtColor, fan.pantColor);
	}
}

#endif // RENDERFANS_H