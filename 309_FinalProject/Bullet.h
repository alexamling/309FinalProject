#pragma once
#include "MyEntity.h"

using namespace Simplex;

class Bullet :
	public MyEntity
{
public:
	Bullet(vector3 offset, matrix4 root);
	~Bullet();
	void Update();
	bool IsActive();
	void SetActive(bool a_bActive);
	bool IsColliding(MyEntity* other);

	matrix4 rootPosition;
	vector3 m_v3Speed;
private:
	CameraManager* m_pCameraMngr = nullptr;
	MyEntity* bulletModel = nullptr;
	vector3 m_v3Velocity;
	bool m_bIsActive=true;
	float m_fSpeed = -0.1f;
};

