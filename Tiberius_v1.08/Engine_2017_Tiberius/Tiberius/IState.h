#pragma once

#include <string>

class IState
{
public:
	IState() {};
	virtual ~IState() {}; 

	virtual void Enter() = 0;
	virtual bool Update(float p_fDelta) = 0;
	virtual void Exit() = 0;
	virtual std::string NextState() = 0;
};