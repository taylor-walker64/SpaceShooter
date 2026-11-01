#include "Level.h"
#include "EnemyManager.h"
#include <iostream>

Level::Level(int levelNumber) {
	this->levelNumber = levelNumber;
	encounterNumber = 1;
	maxEncounters = 3;
	levelComplete = false;
}

void Level::advanceEncounter() {
	if (encounterNumber < maxEncounters) {
		++encounterNumber;
	}

	else {
		levelComplete = true;
		std::cout << "Level complete" << std::endl;
	}
}

void Level::startEncounter(EnemyManager& enemyManager) {
	if (encounterNumber == 1) {
		enemyManager.spawnEnemy(1280, 300);
	}

	else if (encounterNumber == 2) {
		enemyManager.spawnEnemy(1280, 200);
		enemyManager.spawnEnemy(1280, 600);
	}
	
	else if (encounterNumber == 3) {
		enemyManager.spawnEnemy(1280, 450);
		enemyManager.spawnEnemy(1280, 550);
		enemyManager.spawnEnemy(1280, 650);
	}
}

void Level::continueLevel(EnemyManager& enemyManager) {
	if (enemyManager.isEncounterFinished() && !levelComplete) {
		advanceEncounter();
		if (!levelComplete) {
			startEncounter(enemyManager);
		}
	}
}

void Level::reset() {
	encounterNumber = 1;
	levelComplete = false;
}