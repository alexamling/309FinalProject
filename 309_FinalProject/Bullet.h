#pragma once
#include "MyEntity.h"

using namespace Simplex;

class Bullet :
	public MyEntity
{
public:
	Bullet();
	Bullet(vector3 a_v3Velocity);
	~Bullet();
	void Update();
private:
	vector3 velocity;
};

