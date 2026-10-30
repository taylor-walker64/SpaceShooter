#pragma once

class EnemyManager;

class Level {
private:
	int levelNumber;
	int encounterNumber;
	int maxEncounters;
	bool levelComplete;

public:
	Level(int levelNumber);
	void advanceEncounter();
	void startEncounter(EnemyManager&);
	void continueLevel(EnemyManager&);
};