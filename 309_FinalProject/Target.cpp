#include "Target.h"

using namespace Simplex;

float Target::m_fTimer = 0.0f;
float Target::m_fDeltaTime = 0.0f;

Target::Target() : MyEntity("Minecraft\\Target2.fbx", "target")
{
	// get a copy of the point list of the model
	std::vector<vector3> lPointList = GetModel()->GetVertexList();
	
	// remove the pole from the copy list of points
	for (int i = 0; i < lPointList.size(); i++)
	{
		if (lPointList[i].y < 0.01) // the points that have a 0 y are the bottom of the pole
		{
			lPointList.erase(lPointList.begin() + i, lPointList.begin() + i + 1);
			i--;
		}
	}
	
	// set rigid body to be made out of the new list of points
	MyRigidBody* pRigidBody = GetRigidBody();
	*pRigidBody = MyRigidBody(lPointList);
}


Target::~Target()
{ 
}

void Target::UpdateTimer(float a_fDeltaTime) 
{
	if (m_fTimer >= MAX_TIME)
	{
		m_fDeltaTime = 0.0f;
		return;
	}

	m_fTimer += a_fDeltaTime;

	if (m_fTimer >= MAX_TIME)
		m_fDeltaTime = a_fDeltaTime - (m_fTimer - MAX_TIME);
	else
		m_fDeltaTime = a_fDeltaTime;
}

void Target::Rotate() 
{
	//float fTime = glm::clamp(m_fTimer / 20.0f, 0.0f, 1.0f);
	//float fAngle = 0.0f * fTime + (-PI / 2.0f) * (1.0f - fTime);
	float fAngSpeed = (-PI / 2.0f) / MAX_TIME;
	float fDeltaAngle = fAngSpeed * m_fDeltaTime;
	SetModelMatrix(glm::rotate(GetModelMatrix(), fDeltaAngle, AXIS_X));
}

