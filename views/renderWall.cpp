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
	color grey = { 0.5f, 0.5f, 0.5f };

	color colors[4] = { red, green, blue, grey };

	int random = rand() % 4;
	wallColor = colors[random];

	//set the timer to change Color again
	glutTimerFunc(colorChangeInterval, updateWallColor, 0);
}

void initializeWall() {
	updateWallColor(0);
}

void renderWall(float x, float y, float z , bool rotate) {
	glPushMatrix();
	glColor3f(wallColor.r,wallColor.g , wallColor.b);
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