#include "Headers/views/renderPlayer.h"
#include "Headers/views/renderGun.h"
#include <cmath>
#include <glut.h>




void renderPlayer(float posX, float posY, float posZ,float rotX,float rotY,float rotZ, bool isHoldingGun , bool animateGun) {
    glPushMatrix();  // Save the current transformation matrix

    // Position the entire player at (posX, posY, posZ)
    glTranslatef(posX, posY + 0.1, posZ);
	glScalef(0.6f, 0.7f, 0.6f); // Scale down the player
	glRotatef(rotY, 0, 1, 0); // Rotate to face the camera
    
    glColor3f(0.8f, 0.5f, 0.3f);
    // Head (Sphere)
    glPushMatrix();
    glTranslatef(0.0f, 0.7f, 0.0f);  // Position the head above the body
    glutSolidSphere(0.2, 20, 20);    // Radius 0.2, 20 slices, 20 stacks
    glPopMatrix();


    glColor3f(0, 0, 1);
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
    glTranslatef(-0.2f, 0.4f, 0); // Position left arm to the side of body and angled for holding
    glRotatef(20, 0.0f, 1.0f, 1.0f);  // Rotate to align for holding position
    GLUquadric* leftArm = gluNewQuadric();
    gluCylinder(leftArm, 0.05, 0.05, 0.5, 10, 10); // Radius 0.05, height 0.5
    gluDeleteQuadric(leftArm);
    glPopMatrix();

    // Right Arm (Cylinder, holding the gun)
    glPushMatrix();
    glTranslatef(0.2f, 0.4f, 0); // Position right arm to the side of body and angled for holding
    glRotatef(-20, 0.0f, 1.0f, 1.0f); // Rotate to align for holding position
    GLUquadric* rightArm = gluNewQuadric();
    gluCylinder(rightArm, 0.05, 0.05, 0.5, 10, 10); // Radius 0.05, height 0.5
    gluDeleteQuadric(rightArm);
    glPopMatrix();

    // Legs
    glColor3f(0.5f, 0.5f, 0.3f); 

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


    if (isHoldingGun) {
        static float rotAngleAnime = 0;
		if (animateGun) {
			rotAngleAnime = sin(glutGet(GLUT_ELAPSED_TIME) * 0.001) * 15;
		}
		else {
			rotAngleAnime = 0;
		}
		glPushMatrix();
        glTranslatef(0.0f, 0.5f, -0.1f); // Position the gun in the hand
		glRotatef(90, 0.0f, 0.0f, 1.0f); // Rotate to align with Y-axis
		glRotatef(rotAngleAnime, 1.0f, 0.0f, 0.0f); // Rotate to align with X-axis
        renderGun();
		glPopMatrix();
    }


    glPopMatrix(); // Restore the transformation matrix
}