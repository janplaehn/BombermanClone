#pragma once
class GameManager
{
public:
	void setplayerposx(int x);
	void setplayerposy(int y);
	int getplayerposx();
	int getplayerposy();
	int getLives();
	void setLives(int x);
	int getBombReach();
	void setBombReach(int reach);
	int getEnemyNumber();
	void setEnemyNumber(int num);
	int getMaxBombNumber();
	void setMaxBombNumber(int num);
	int getCurrentBombNumber();
	void setCurrentBombNumber(int num);
	int getScore();
	void setScore(int x);
	int getRemainingTime();
	void setRemainingTime(int time);
	GameManager();
	~GameManager();
	void setIsOpen(bool b);
	bool getIsOpen();
private:
	int lives;
	int playerposx;
	int playerposy;
	int bombReach;
	int enemyNumber;
	int maxBombNumber;
	int currentBombNumber;
	int score;
	int remainingTime;
	bool isOpen;
};

