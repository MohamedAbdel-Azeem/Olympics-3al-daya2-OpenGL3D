#include "Headers/views/renderWall.h"
#include <ctime>
#include <cmath>
#include <glut.h>


const int colorChangeInterval = 2000; //2000 ms = 2 seconds

struct color {
	float r, g, b;
};

static color wallColor = { 0.5f, 0.5f, 0.5f };

void updateWallColor(int value) {
	color red = { 1.0f, 0.0f, 0.0f };
	color green = { 0.0f, 1.0f, 0.0f };
	color blue = { 0.0f, 0.0f, 1.0f };

	color colors[4] = { red, green, blue };

	int random = rand() % 3;
	wallColor = colors[random];

	//set the timer to change Color again
	glutTimerFunc(colorChangeInterval, updateWallColor, 0);
}

void initializeWall() {
	updateWallColor(0);
}

void renderLamp(bool rotate) {
	

	if (rotate) {
		glPushMatrix();
		glPushMatrix();
		glColor3f(wallColor.r, wallColor.g, wallColor.b);
		glTranslatef(-0.02, 0.8, 0);
		glScalef(0.05, 0.2, 0.5);
		glutSolidCube(1);
		glPopMatrix();
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0, 0.5, 0);
		glColor3f(0.1, 0.1, 0.1);
		glScalef(0.005, 0.5, 0.3);
		glutSolidCube(1);
		glPopMatrix();
		glPopMatrix();
	}
	else {
		glPushMatrix();
		glPushMatrix();
		glColor3f(wallColor.r, wallColor.g, wallColor.b);
		glTranslatef(0, 0.8, -0.02);
		glScalef(0.5, 0.2, 0.05);
		glutSolidCube(1);
		glPopMatrix();
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0, 0.5, 0);
		glColor3f(0.1, 0.1, 0.1);
		glScalef(0.3, 0.5, 0.005);
		glutSolidCube(1);
		glPopMatrix();
		glPopMatrix();
	}


}



void renderWall(float x, float y, float z , bool rotate) {

	// Cube or Wall it self

	if (rotate) {
		glPushMatrix();
		glPushMatrix();
		glColor3f(wallColor.r, wallColor.g, wallColor.b);
		glScalef(5, 1, 0.2);
		glTranslatef(x, y, z);
		glutSolidCube(1);
		renderLamp(rotate);
		glPopMatrix();
		glPopMatrix();
	}
	else {
		glPushMatrix();
		glPushMatrix();
		glColor3f(wallColor.r, wallColor.g, wallColor.b);
		glScalef(0.2, 1, 5);
		glTranslatef(x, y, z);
		glutSolidCube(1);
		renderLamp(rotate);
		glPopMatrix();

		glPopMatrix();
	}


	

}