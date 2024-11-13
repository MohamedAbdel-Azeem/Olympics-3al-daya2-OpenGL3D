#pragma once
#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
	float posX, posY, posZ;
	float rotX, rotY, rotZ;
	bool isHoldingGun;
	bool didCollectBullet;
	Player(float _posX = 0.0f, float _posY = 0.5f, float _posZ = 2.0f, float _rotX = 0.0f, float _rotY = 0.0f, float _rotZ = 0.0f) {
		posX = _posX;
		posY = _posY;
		posZ = _posZ;
		rotX = _rotX;
		rotY = _rotY;
		rotZ = _rotZ;
		isHoldingGun = false;
		didCollectBullet = false;
	}
	void move(float x, float y, float z) {

		float zBoundsWithoutGun = -2.0f;
		float zBoundsWithGun = 1.0f;

		float usedLeftXBounds = isHoldingGun ? 1.0f : 2.2f;
		float usedRightXBounds = isHoldingGun ? -1.4 : -2.2f;

		float usedZBounds = isHoldingGun? zBoundsWithGun : zBoundsWithoutGun;

		if (posX >= 0.8 && posZ >= 1.7 && posZ <= 2.3)
			isHoldingGun = true;

		if (posX + x < usedLeftXBounds && posX + x > usedRightXBounds)
			posX += x;
		posY += y;
		if (posZ + z < 2.2 && posZ + z > usedZBounds)
		posZ += z;
	}
	void rotate(float x, float y, float z) {
		rotX += x;
		rotY += y;
		rotZ += z;
	}

	void holdGun() {
		if (posX >= 0.8 && posZ >= 1.7 && posZ <= 2.3)
			isHoldingGun = true;
	}

};

#endif 