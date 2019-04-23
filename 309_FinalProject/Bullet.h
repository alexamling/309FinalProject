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
	bool IsActive();
	void SetActive(bool a_bActive);
	bool IsColliding(MyEntity* other);
private:
	vector3 m_v3Velocity;
	bool m_bIsActive;
	vector3 m_v3Speed;
};

