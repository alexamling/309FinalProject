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
	bool IsActive();
	void SetActive(bool a_bActive);
	bool IsColliding(MyEntity* other);
private:
	vector3 m_v3Velocity;
	bool m_bIsActive
};

