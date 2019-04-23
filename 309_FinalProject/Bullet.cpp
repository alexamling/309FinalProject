#include "Bullet.h"


Bullet::Bullet() : MyEntity("data\MOBJ\Bullet.obj", "bullet") {
	Bullet(vector3(0));
}

Bullet::Bullet(vector3 a_v3Velocity) : MyEntity("data\MOBJ\Bullet.obj", "bullet")
{
	// TODO: Set model rotation to be in-line with movement
}


Bullet::~Bullet()
{

}

void Bullet::Update()
{
	if(m_bIsActive)
	{
		//GetRigidBody()->Move(m_v3Velocity);
			
	}
}

bool Bullet::IsActive() {
	return m_bIsActive;
}

void Bullet::SetActive(bool a_bActive) {
	m_bIsActive = a_bActive;
}

bool Bullet::IsColliding(MyEntity* other) {
	return false;
}