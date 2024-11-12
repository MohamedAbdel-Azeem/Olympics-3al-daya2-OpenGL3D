#pragma once
#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
	float posX, posY, posZ;
	float rotX, rotY, rotZ;
	bool isHoldingGun;
	Player(float _posX = 0.0f, float _posY = 0.5f, float _posZ = 0.3f, float _rotX = 0.0f, float _rotY = 0.0f, float _rotZ = 0.0f) {
		posX = _posX;
		posY = _posY;
		posZ = _posZ;
		rotX = _rotX;
		rotY = _rotY;
		rotZ = _rotZ;
		isHoldingGun = true;
	}
	void move(float x, float y, float z) {
		if (posX + x < 1 && posX + x > -1.4)
			posX += x;
		posY += y;
		if (posZ + z < 2.2 && posZ + z > -2)
		posZ += z;
	}
	void rotate(float x, float y, float z) {
		rotX += x;
		rotY += y;
		rotZ += z;
	}

	void holdGun() {
		isHoldingGun = true;
	}

};

#endif 