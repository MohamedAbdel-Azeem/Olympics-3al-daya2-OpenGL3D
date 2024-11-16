#pragma once

#include <iostream>
#include "fmod.hpp"

#define GameOver_Sound "Assets/Game_Lose.mp3"
#define GameEnd_Sound "Assets/Game_Win.mp3"
#define Background_Sound "Assets/Sports Stadium Crowd Cheering Sound Effect [TubeRipper.com].mp3"
#define GunShot_Sound "Assets/Gun shot sound effect.mp3"
#define GunReload_Sound "Assets/Gun_reload.mp3"

FMOD_RESULT result;
FMOD::System* pSystem = nullptr;
FMOD::Channel* backgroundChannel = nullptr;
FMOD::Channel* pChannel = nullptr;
FMOD::Channel* pChannel2 = nullptr; // for Game Win/Lose

void SoundPlayer_init() {
    // First, create the FMOD system
    result = FMOD::System_Create(&pSystem); // Create the system object
    if (result != FMOD_OK) {
        std::cout << "FMOD System creation failed" << std::endl;
        return;
    }

    // Then initialize the system
    result = pSystem->init(32, FMOD_INIT_NORMAL, nullptr); // Initialize FMOD system with 32 channels
    if (result != FMOD_OK) {
        std::cout << "FMOD System initialization failed" << std::endl;
    }
}

void SoundPlayer_playBackgroundMusic() {
    FMOD::Sound* pSound = nullptr;
    backgroundChannel->stop();
    pChannel->stop();
    // Ensure the sound path is correctly formatted
    result = pSystem->createSound(Background_Sound, FMOD_DEFAULT, nullptr, &pSound);

    if (result != FMOD_OK) {
        std::cout << "Error creating sound" << std::endl;
        return;
    }

    result = pSystem->playSound(pSound, nullptr, false, &backgroundChannel);

    if (result != FMOD_OK) {
        std::cout << "Error playing sound" << std::endl;
    }
    else {
        std::cout << "Sound played successfully" << std::endl;
    }
}

void SoundPlayer_playGameOverMusic() {
    bool isPlaying = false;
	backgroundChannel->stop();
    if (pChannel2) {
        pChannel2->isPlaying(&isPlaying);
    }
    if (isPlaying) {
        return; // Do nothing if the game over music is already playing
    }

    FMOD::Sound* pSound = nullptr;
    result = pSystem->createSound(GameOver_Sound, FMOD_DEFAULT, nullptr, &pSound);
    if (result != FMOD_OK) {
        std::cout << "Error creating sound" << std::endl;
        return;
    }
    result = pSystem->playSound(pSound, nullptr, false, &pChannel2);
    if (result != FMOD_OK) {
        std::cout << "Error playing sound" << std::endl;
    }
    else {
        std::cout << "Sound played successfully" << std::endl;
    }
}

void SoundPlayer_playGameEndMusic() {
    bool isPlaying = false;
	backgroundChannel->stop();
    if (pChannel2) {
        pChannel2->isPlaying(&isPlaying);
    }
    if (isPlaying) {
        return; // Do nothing if the game end music is already playing
    }

    FMOD::Sound* pSound = nullptr;
    result = pSystem->createSound(GameEnd_Sound, FMOD_DEFAULT, nullptr, &pSound);
    if (result != FMOD_OK) {
        std::cout << "Error creating sound" << std::endl;
        return;
    }
    result = pSystem->playSound(pSound, nullptr, false, &pChannel2);
    if (result != FMOD_OK) {
        std::cout << "Error playing sound" << std::endl;
    }
    else {
        std::cout << "Sound played successfully" << std::endl;
    }
}

void SoundPlayer_playGunShotMusic() {
	FMOD::Sound* pSound = nullptr;
	// Ensure the sound path is correctly formatted
	result = pSystem->createSound(GunShot_Sound, FMOD_DEFAULT, nullptr, &pSound);
	if (result != FMOD_OK) {
		std::cout << "Error creating sound" << std::endl;
		return;
	}
	result = pSystem->playSound(pSound, nullptr, false, &pChannel);
	if (result != FMOD_OK) {
		std::cout << "Error playing sound" << std::endl;
	}
	else {
		std::cout << "Sound played successfully" << std::endl;
	}
}


void SoundPlayer_PlayGunReload() {
	FMOD::Sound* pSound = nullptr;

	result = pSystem->createSound(GunReload_Sound, FMOD_DEFAULT, nullptr, &pSound);
	if (result != FMOD_OK) {
		std::cout << "Error creating sound" << std::endl;
		return;
	}
	result = pSystem->playSound(pSound, nullptr, false, &pChannel);
	if (result != FMOD_OK) {
		std::cout << "Error playing sound" << std::endl;
	}
	else {
		std::cout << "Sound played successfully" << std::endl;
	}
}