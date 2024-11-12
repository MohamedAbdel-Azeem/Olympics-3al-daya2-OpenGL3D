#include "Headers/views/renderGun.h"
#include <glut.h>

void renderGun() {
	
	glPushMatrix();
	// Gun (Cuboid)
	glColor3f(0.1f, 0.1f, 0.1f); // Dark gray for the gun

	// rifle itself
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.7f);   // Position in front of the player’s hands
	glScalef(0.1f, 0.1f, 1.5f);       // Scale to make a cuboid shape
	glutSolidCube(0.4);                // Create a cuboid with cube function
	glPopMatrix();

	// rifle holder
	glPushMatrix();
	glTranslatef(-0.1f, 0.0f, 0.42f);   // Position in front of the player’s hands
	glScalef(0.5f, 0.1f, 0.1f);       // Scale to make a cuboid shape
	glutSolidCube(0.4);                // Create a cuboid with cube function
	glPopMatrix();

	//rifle Barrel
	glPushMatrix();
	glTranslatef(-0.16f, 0.0f, 0.7f);   // Position in front of the player’s hands
	glScalef(0.9f, 0.1f, 0.1f);       // Scale to make a cuboid shape
	glutSolidCube(0.4);                // Create a cuboid with cube function
	glPopMatrix();

	glPopMatrix();
}