#include "Player.h"

using namespace Simplex;

Player::Player(Camera* a_pCamera)
{
	m_pCamera = a_pCamera;
	m_pEntityMngr = MyEntityManager::GetInstance();
	Init();
}


Player::~Player()
{
	Release();
}

void Simplex::Player::MoveForward(float a_fDistance)
{
	vector3 v3Forward = m_pCamera->GetForward();
	m_v3Position = m_v3Position + a_fDistance * glm::normalize(vector3(v3Forward.x, 0.0f, v3Forward.z));
}

void Simplex::Player::MoveSideways(float a_fDistance)
{
	vector3 v3Sideways = a_fDistance * glm::normalize(glm::cross(m_pCamera->GetForward(), AXIS_Y));
	m_v3Position = m_v3Position + v3Sideways;
}

vector3 Simplex::Player::GetPosition() { return m_v3Position; }

void Simplex::Player::SetPosition(vector3 a_v3Position){ m_v3Position = a_v3Position; }

void Simplex::Player::SetGun(Model* a_pGun) { m_pGun = a_pGun; }

void Simplex::Player::ShootGun()
{}

void Simplex::Player::Update() 
{
	if(m_pCamera != nullptr)
		m_pCamera->SetPositionTargetAndUpward(
			m_v3Position,
			m_v3Position + m_pCamera->GetForward(),
			AXIS_Y
		);

	if (m_pGun == nullptr)
		return;
	if (sighted == false) {
		m_pGun->SetModelMatrix(
			glm::rotate(
				glm::translate(m_pCamera->GetCameraSpaceAdjusted(), vector3(0.5f, -0.25f, 0.25f)),
				static_cast<float>(-PI / 2.0f),
				AXIS_Y)
		);
	}
	if (sighted == true) {
		m_pGun->SetModelMatrix(
			glm::rotate(
				glm::translate(m_pCamera->GetCameraSpaceAdjusted(), vector3(0.0f, -0.1f, 0.25f)),
				static_cast<float>(-PI / 2.0f),
				AXIS_Y)
		);
	}
	m_pGun->AddToRenderList();
}

void Simplex::Player::Shoot() 
{

}

void Simplex::Player::Ironsights() {
	sighted = !sighted;
}

void Simplex::Player::Init()
{
	m_v3Position = vector3(0.0f, 0.0f, 0.0f);

	//Set the position and target of the camera
	m_pCamera->SetPositionTargetAndUpward(
		m_v3Position, //Position
		vector3(0.0f, 0.0f, 99.0f),	//Target
		AXIS_Y);					//Up
}

void Simplex::Player::Release()
{
	m_pCamera = nullptr;
	m_pGun = nullptr;
}
