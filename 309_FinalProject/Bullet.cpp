#include "Bullet.h"

Bullet::Bullet(vector3 offset, matrix4 root) : MyEntity("Minecraft\\bullet5.fbx", "bullet") {
	m_pCameraMngr = CameraManager::GetInstance();
	rootPosition = glm::translate(root, offset);
	this->m_v3Speed = vector3(-0.0f, 0.0f, m_fSpeed);
	this->SetModelMatrix(rootPosition);
}

Bullet::~Bullet()
{

}

void Bullet::Update()
{
	//m_pRigidbody->SetModelMatrix(this->GetModelMatrix());
}

bool Bullet::IsActive() {
	return m_bIsActive;
}

void Bullet::SetActive(bool a_bActive) {
	m_bIsActive = a_bActive;
}