#pragma once
#include <vector>

class LevelManager {
public:
	LevelManager();
	~LevelManager();
	int getCurrentLevel();
	void setCurrentLevel(int x);
	int getUnlockedLevelNumber();
	void increaseUnlockedLevelNumber();
	std::vector<int> getLevelTiles();
private:
	int unlockedLevelNumber;
	int currentLevel;
	std::vector<int> multiplayerLevel;
	std::vector<int> level1;
	std::vector<int> level2;
	std::vector<int> level3;
	std::vector<int> level4;
	std::vector<int> level5;
	std::vector<int> level6;
	std::vector<int> level7;
	std::vector<int> level8;
	std::vector<int> level9;
	enum tiles {FLOOR, WALL, BRICK, PLAYER, ENEMY1, ENEMY2, ENEMY3, ENEMY4, ENEMY5, ENEMY6, ENEMY7, DOOR};
};

