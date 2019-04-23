#include "Bullet.h"

Bullet::Bullet() : MyEntity("data\MOBJ\Bullet.obj", "bullet") {
	this->m_v3Speed = vector3(1.0f, 1.0f, 1.0f);
}

Bullet::~Bullet()
{

}

void Bullet::Update()
{
	if(m_bIsActive)
	{
		this->SetModelMatrix(glm::translate(IDENTITY_M4, m_v3Speed));
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