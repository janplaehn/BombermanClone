#include "stdafx.h"
#include "GameManager.h"

GameManager::GameManager() {
	bombReach = 2;
	enemyNumber = 0;
	maxBombNumber = 1;
	currentBombNumber = 0;
	score = 1000;
	remainingTime = 400;
	isOpen = false;
	lives = 2;
}

GameManager::~GameManager() {
}

void GameManager::setIsOpen(bool b) {
	isOpen = b;
}

bool GameManager::getIsOpen()
{
	return isOpen;
}

void GameManager::setplayerposx(int x) {
	playerposx = x;
}

void GameManager::setplayerposy(int y) {
	playerposy = y;
}

int GameManager::getplayerposx() {
	return playerposx;
}

int GameManager::getplayerposy() {
	return playerposy;
}

int GameManager::getLives() {
	return lives;
}

void GameManager::setLives(int x){
	lives = x;
}

int GameManager::getBombReach() {
	return bombReach;
}

void GameManager::setBombReach(int reach) {
	bombReach = reach;
}

int GameManager::getEnemyNumber() {
	return enemyNumber;
}

void GameManager::setEnemyNumber(int num) {
	enemyNumber = num;
}

int GameManager::getMaxBombNumber() {
	return maxBombNumber;
}

void GameManager::setMaxBombNumber(int num) {
	maxBombNumber = num;
}

int GameManager::getCurrentBombNumber()
{
	return currentBombNumber;
}

void GameManager::setCurrentBombNumber(int num) {
	currentBombNumber = num;
}

int GameManager::getScore() {
	return score;
}

void GameManager::setScore(int x) {
	score = x;
}

int GameManager::getRemainingTime() {
	return remainingTime;
}

void GameManager::setRemainingTime(int time) {
	remainingTime = time;
}