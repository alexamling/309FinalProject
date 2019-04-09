#pragma once
#include "MyEntity.h"

using namespace Simplex;

class Bullet :
	public MyEntity
{
public:
	Bullet();
	~Bullet();
	void Update();
private:
	float speed;
};

