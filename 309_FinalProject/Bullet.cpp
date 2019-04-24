#include "Bullet.h"

Bullet::Bullet(vector3 offset, matrix4 root) : MyEntity("Minecraft\\bullet4.fbx", "bullet") {
	m_pCameraMngr = CameraManager::GetInstance();
	rootPosition = glm::translate(root, offset);
	this->m_v3Speed = vector3(-0.0f, 0.0f, -0.1f);
	this->SetModelMatrix(rootPosition);
	//bulletModel->Load("Minecraft\\bullet4.fbx");
}

Bullet::~Bullet()
{

}

void Bullet::Update()
{
	//if(m_bIsActive)
	//{
	
	//}
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