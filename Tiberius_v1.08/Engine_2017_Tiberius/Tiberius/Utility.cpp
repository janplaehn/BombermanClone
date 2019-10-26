#include "stdafx.h"
#include "Utility.h"
#include <random>
#include <chrono>


Utility::Utility() {}


Utility::~Utility() {}

int Utility::random(int min, int max) {
	static std::random_device rd;
	static std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(min, max);
	return distr(eng);
}

unsigned long long Utility::get_time() {
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}
