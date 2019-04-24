#include "Bullet.h"

Bullet::Bullet(vector3 forward, matrix4 root) : MyEntity("Minecraft\\bullet4.fbx", "bullet") {
	m_pCameraMngr = CameraManager::GetInstance();
	rootPosition = glm::translate(root, vector3(0.5f, -0.25f, 0.25f));
	this->m_v3Speed = forward*m_fSpeed;
	this->SetModelMatrix(root);
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