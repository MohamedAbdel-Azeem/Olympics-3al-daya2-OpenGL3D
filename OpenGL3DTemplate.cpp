#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <glut.h>
#include <math.h>
#include <chrono>
#include <thread>
#include <string>
#include <ctime>
#include "Headers/views/renderGround.h"
#include "Headers/views/renderWall.h"
#include "Headers/views/renderPlayer.h"
#include "Headers/model/player.h"
#include "Headers/views/renderFence.h"
#include "Headers/views/renderTable.h"
#include "Headers/views/renderTarget.h"
#include "Headers/views/renderFans.h"
#include "Headers/views/renderChair.h"
#include "Headers/views/renderLaser.h"
#include "Headers/SoundPlayer.h"
#pragma comment(lib, "User32.lib")
#define DEG2RAD(a) (a * 0.0174532925)

using namespace std;
using namespace std::chrono;

Player player;

int mouseX, mouseY;
int windowWidth = 960, windowHeight = 640; // Increased window size
bool isMouseLocked = true; // Flag to lock the mouse inside

bool animateFans = false;
bool animateTable = false;
bool animateGun = false;
bool animateBullet = false;
bool animateFence = false;
bool animateChair = false;

bool isGameLose = false;
bool isGameWin = false;

steady_clock::time_point startTime;
const int GAME_TIME = 20;

float sphere1X, sphere1Y, sphere1Z, sphere2X, sphere2Y, sphere2Z;

float moveSpeed = 0.05f; // Camera movement speed

// Key state tracking
bool keys[256] = { false };  // Track the state of each key (false by default)

void centerMouse() {
    POINT windowCenter;
    windowCenter.x = windowWidth / 2;
    windowCenter.y = windowHeight / 2;
    ClientToScreen(GetActiveWindow(), &windowCenter);
    SetCursorPos(windowCenter.x, windowCenter.y);
}


class Vector3f {
public:
    float x, y, z;

    Vector3f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) {
        x = _x;
        y = _y;
        z = _z;
    }

    Vector3f operator+(Vector3f& v) {
        return Vector3f(x + v.x, y + v.y, z + v.z);
    }

    Vector3f operator-(Vector3f& v) {
        return Vector3f(x - v.x, y - v.y, z - v.z);
    }

    Vector3f operator*(float n) {
        return Vector3f(x * n, y * n, z * n);
    }

    Vector3f operator/(float n) {
        return Vector3f(x / n, y / n, z / n);
    }

    Vector3f unit() {
        return *this / sqrt(x * x + y * y + z * z);
    }

    Vector3f cross(Vector3f v) {
        return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
    }
};

class Cam {
public:
    Vector3f eye, center, top;

    Cam(float X = 1.0f, float Y = 1.0f, float Z = 5.0f, float cenX = 0.0f, float cenY = 0.0f, float cenZ = 0.0f, float upX = 0.0f, float upY = 1.0f, float upZ = 0.0f) {
        eye = Vector3f(X, Y, Z);
        center = Vector3f(cenX, cenY, cenZ);
        top = Vector3f(upX, upY, upZ);
    }

    void look() {
        gluLookAt(
            eye.x, eye.y, eye.z,
            center.x, center.y, center.z,
            top.x, top.y, top.z
        );
    }

    void moveForward(float distance) {
        Vector3f view = (center - eye).unit();
        eye = eye + view * distance;
        center = center + view * distance;
    }

    void moveRight(float distance) {
        Vector3f view = (center - eye).unit();
        Vector3f right = view.cross(top).unit();
        eye = eye + right * distance;
        center = center + right * distance;
    }

    void moveUp(float distance) {
        eye = eye + top * distance;
        center = center + top * distance;
    }

    void rotateX(float a) {
        Vector3f view = (center - eye).unit();
        Vector3f right = top.cross(view).unit();
        view = view * cos(DEG2RAD(a)) + top * sin(DEG2RAD(a));
        top = view.cross(right);
        center = eye + view;
    }

    void rotateY(float a) {
        Vector3f view = (center - eye).unit();
        Vector3f right = top.cross(view).unit();
        view = view * cos(DEG2RAD(a)) + right * sin(DEG2RAD(a));
        right = view.cross(top);
        center = eye + view;
    }

    void reset() {
		eye = Vector3f(1.0f, 1.0f, 5.0f);
		center = Vector3f(0.0f, 0.0f, 0.0f);
		top = Vector3f(0.0f, 1.0f, 0.0f);
    }
};

Cam camera;

void MouseMovement(int x, int y) {
    if (isMouseLocked) {
        int dx = x - windowWidth / 2;
        int dy = y - windowHeight / 2;

        float sensitivity = -0.1f;
        camera.rotateY(dx * sensitivity);
        camera.rotateX(dy * sensitivity);

        centerMouse();
    }

    glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y) {
    keys[key] = true;  // Set the key state to true when the key is pressed
}

void KeyboardUp(unsigned char key, int x, int y) {
    keys[key] = false;  // Set the key state to false when the key is released
}


void cam() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float)windowWidth / (float)windowHeight, 0.001, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    camera.look();
}

void controlKeyboard() {
    if (keys['w']) {
        camera.moveForward(moveSpeed);
    }
    if (keys['s']) {
        camera.moveForward(-moveSpeed);
    }
    if (keys['a']) {
        camera.moveRight(-moveSpeed);
    }
    if (keys['d']) {
        camera.moveRight(moveSpeed);
    }
    if (keys[' ']) {
        camera.moveUp(moveSpeed);
    }
    if (keys['c']) {
        camera.moveUp(-moveSpeed);
    }
    if (keys['t']) {
        camera.eye = Vector3f(0, 5, 0);
        camera.center = Vector3f(0, 0, 0);
        camera.top = Vector3f(0, 0, -1);
    }
    if (keys['y']) {
        camera.eye = Vector3f(5, 0, 0);
        camera.center = Vector3f(0, 0, 0);
        camera.top = Vector3f(0, 1, 0);
    }
    if (keys['u']) {
        camera.eye = Vector3f(0, 0, 5);
        camera.center = Vector3f(0, 0, 0);
        camera.top = Vector3f(0, 1, 0);
    }
	if (keys['f']) {
		animateFans = !animateFans;
		keys['f'] = false;
	}
	if (keys['r']) {
		player.rotate();
		keys['r'] = false;
	}
    if (keys['h']) {
		animateTable = !animateTable;
        keys['h'] = false;
    }
    if (keys['g']) {
		animateGun = !animateGun;
		keys['g'] = false;
    }
    if (keys['b']) {
		animateBullet = !animateBullet;
		keys['b'] = false;
    }
    if (keys['v']) {
		animateFence = !animateFence;
		keys['v'] = false;
    }
    if (keys['j']) {
		animateChair = !animateChair;
		keys['j'] = false;
    }
    if (keys['m']) {
		player.shoot(sphere1X, sphere1Y, sphere1Z, 0.05, sphere2X, sphere2Y, sphere2Z, 0.15);
		keys['m'] = false;
    }
    if (keys[27]) {
        isMouseLocked = false;
        exit(EXIT_SUCCESS);
    }
}


void controlPlayerKeyboard(int key, int x, int y) {
	float playerSpeed = 0.1f;
    switch (key) {
    case GLUT_KEY_UP:
		player.move(0, 0, -playerSpeed);
        break;
    case GLUT_KEY_DOWN:
		player.move(0, 0, playerSpeed);
        break;
    case GLUT_KEY_LEFT:
		player.move(-playerSpeed, 0, 0);
        break;
    case GLUT_KEY_RIGHT:
		player.move(playerSpeed, 0, 0);
        break;
    default:
        break;
    }
}

void renderBitmapString(float x, float y, void* font, const char* string) {
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(x, y);
    while (*string) {
        glutBitmapCharacter(font, *string);
        string++;
    }
}

int getTime() {
	return duration_cast<seconds>(steady_clock::now() - startTime).count();
}


void Display(void) {
    

    if (isGameWin) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		camera.reset();
		std::string score = "You Won! Your Score is: " + std::to_string(player.score);
		renderBitmapString(-0.5, 0, GLUT_BITMAP_TIMES_ROMAN_24, score.c_str());
		glFlush();
		SoundPlayer_playGameEndMusic();
		return;
    }

    if (isGameLose) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        camera.reset();
		renderBitmapString(-0.5, 0, GLUT_BITMAP_TIMES_ROMAN_24, "Game Over, Time is Up!");
		glFlush();
        SoundPlayer_playGameOverMusic();
		return;
    }


    cam();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderGround();
	renderWall(12, 0.5, 0,false);
	renderWall(-12, 0.5, 0,false);
	renderWall(0, 0.5, -12,true);

    renderFence(1.5, 0.2, -2.2 , 2.8 , animateFence);
    renderFence(-1.5, 0.2, -2.2 , 2.8 , animateFence);

	renderTable(1.2, 0, 1.5f, ! player.isHoldingGun,!player.didCollectBullet,animateTable,animateGun, animateBullet);

	renderPlayer(player.posX, player.posY, player.posZ, player.rotX , player.rotY, player.rotZ , player.isHoldingGun , animateGun);

    renderTarget(0,0.1,-1.8, sphere1X, sphere1Y, sphere1Z, sphere2X, sphere2Y, sphere2Z);

    renderFans(animateFans);

	renderChair(-1, 0, 1.5, animateChair);
    
    int timeLeft = GAME_TIME - getTime();
    std::string time_left = "Time Left: " + std::to_string(timeLeft);

	renderBitmapString(1.5, 2.5, GLUT_BITMAP_TIMES_ROMAN_24, time_left.c_str());

	std::string objective1 = "Objective: Collect the Gun";
	std::string objective2 = "Objective: Collect the Bullet";
	std::string objective3 = "Objective: Shoot the Target using 3 bullets";
	renderBitmapString(1.5, 3.0, GLUT_BITMAP_TIMES_ROMAN_24, objective3.c_str());
	renderBitmapString(1.5, 3.5, GLUT_BITMAP_TIMES_ROMAN_24, objective2.c_str());
	renderBitmapString(1.5, 4.0, GLUT_BITMAP_TIMES_ROMAN_24, objective1.c_str());


	if (player.isHoldingGun && player.didCollectBullet)
        renderLaser(player.posX, player.posY, player.posZ);

    glFlush();
}

static void Timer(int value) {


    if (player.bulletsUsed == 3) {
		isGameWin = true;
		camera.reset();
    }

	if (getTime() >= GAME_TIME) {
		isGameLose = true;
		camera.reset();
    }

	controlKeyboard();
	glutPostRedisplay();
	glutTimerFunc(16, Timer, 0);
}

static void game_init() {
	player = Player();
    initializeWall();
    initializeFans(-1.0f, 1.8, 0, -1.0);
	initializeFans(-1.0f, -1.8, 0, 1.0);
	initializeFenceAnimation();
	startTime = steady_clock::now();
	SoundPlayer_init();
	SoundPlayer_playBackgroundMusic();
}


void main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(150, 150);
    game_init();
    glutCreateWindow("Olympics 3al daya2");
    glutDisplayFunc(Display);
    glutKeyboardFunc(Keyboard);
    glutKeyboardUpFunc(KeyboardUp);
    glutPassiveMotionFunc(MouseMovement);
    glutSetCursor(GLUT_CURSOR_NONE);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glClearColor(0.53f, 0.81f, 0.92f, 0.0f);

	glutTimerFunc(0,Timer, 0);
	glutSpecialFunc(controlPlayerKeyboard);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    centerMouse();
    glutMainLoop();
}