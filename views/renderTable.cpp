#include "Headers/views/renderTable.h"
#include "Headers/views/renderGun.h"
#include "Headers/views/renderBullet.h"
#include <cmath>
#include <glut.h>

void renderTable(float posX, float posY, float posZ, bool havingGun, bool havingBullet, bool animateTable, bool animateGun, bool animateBullet){
    float tableWidth = 2.0f;
    float tableHeight = 0.1f;
    float legRadius = 0.1f;
    float legHeight = 1.0f;

    static float yExtraScale = 0;
	static float zExtraScale = 0;

	if (animateTable) {
		yExtraScale = sin(glutGet(GLUT_ELAPSED_TIME) * 0.001) * 0.1;
		zExtraScale = sin(glutGet(GLUT_ELAPSED_TIME) * 0.001) * 0.1;
    }
    else {
		yExtraScale = 0;
		zExtraScale = 0;
    }

    // Move to table position
    glPushMatrix();
    glTranslatef(posX, posY, posZ);
	glScalef(0.2f, 0.5f+yExtraScale, 0.5f+zExtraScale); // Scale down the table

    // Render table top (cube)
    glPushMatrix();
    glColor3f(0.55f, 0.27f, 0.07f); // Brown color for a wooden look
    glTranslatef(0.0f, legHeight, 0.0f);
    glScalef(tableWidth, tableHeight, tableWidth);
    glutSolidCube(1.0f); // Tabletop
    glPopMatrix();

    // Render legs (cylinders)
    GLUquadric* quad = gluNewQuadric();

    glColor3f(0, 0, 0);

    // Leg 1
    glPushMatrix();
    glTranslatef(tableWidth / 2 - legRadius, 1.0f, tableWidth / 2 - legRadius);
    glRotatef(90, 1.0f, 0.0f, 0.0f);
    gluCylinder(quad, legRadius, legRadius, legHeight, 20, 20);
    glPopMatrix();

    // Leg 2
    glPushMatrix();
    glTranslatef(-tableWidth / 2 + legRadius, 1.0f, tableWidth / 2 - legRadius);
    glRotatef(90, 1.0f, 0.0f, 0.0f);
    gluCylinder(quad, legRadius, legRadius, legHeight, 20, 20);
    glPopMatrix();

    // Leg 3
    glPushMatrix();
    glTranslatef(tableWidth / 2 - legRadius, 1.0f, -tableWidth / 2 + legRadius);
    glRotatef(90, 1.0f, 0.0f, 0.0f);
    gluCylinder(quad, legRadius, legRadius, legHeight, 20, 20);
    glPopMatrix();

    // Leg 4
    glPushMatrix();
    glTranslatef(-tableWidth / 2 + legRadius, 1.0f, -tableWidth / 2 + legRadius);
    glRotatef(90, 1.0f, 0.0f, 0.0f);
    gluCylinder(quad, legRadius, legRadius, legHeight, 20, 20);
    glPopMatrix();

    // Cleanup
    gluDeleteQuadric(quad);


    if (havingGun) {
        static float gunRotAngle = 0;
		if (animateGun) {
			gunRotAngle = sin(glutGet(GLUT_ELAPSED_TIME) * 0.001) * 60;
		}
		else {
			gunRotAngle = 0;
		}
		glPushMatrix();
		glTranslatef(0.0f, 1.05f, -0.2f);
		glRotatef(gunRotAngle, 0.0f, 1.0f, 0.0f);
        renderGun();
        glPopMatrix();
    }

	if (havingBullet) {
		glPushMatrix();
		    glScalef(2.0f, 1.5f, 2.0f);
		    renderBullet(0.0f, 0.7f, 0, animateBullet, !havingBullet);
		glPopMatrix();
	}


    glPopMatrix();
}