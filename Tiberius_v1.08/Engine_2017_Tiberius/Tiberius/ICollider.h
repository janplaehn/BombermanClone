#pragma once

enum COLLIDERTYPE
{
	RECTANGLE,
	SPHERE, //TODO: Not a todo but a note (NOT IMPLEMENTED)
	NOT_SET
};

class ICollider
{
public:
	ICollider() {};
	virtual ~ICollider() {};
	virtual COLLIDERTYPE GetType() = 0;
private:
};