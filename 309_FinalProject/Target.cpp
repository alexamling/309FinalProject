#include "Target.h"

using namespace Simplex;

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

void Target::StartRotate(Bullet *a_pBullet)
{
	// get bullet position on target and calculate radius for angular momentum
	vector3 v3BPos = a_pBullet->GetRigidBody()->GetCenterGlobal();
	float fRadius = (v3BPos.y - GetPivotGlobal().y) / sinf(m_fOrientationX);
	m_fRadii.push_back(fRadius);

	// use angular momentum calculation to determine the speed ~ estimation
	float fAngSpeed = (3 * BULLET_MASS * a_pBullet->m_v3Speed.z) /
		(TARGET_MASS * fRadius);

	// use orientation to determine in which way the bullet was shot
	float fOrientation = glm::dot(
		matrix3(a_pBullet->GetModelMatrix()) * AXIS_Z,
		matrix3(GetModelMatrix()) * AXIS_Z
	) >= 0 ? 1.0f : -1.0f;

	m_fOrientations.push_back(fOrientation);

	// get velocity by multiplying direction times speed
	m_fAngVelocity = fOrientation * fAngSpeed;

	//a_pBullet->SetActive(false); // deactivate bullet
	m_lBulletsStuck.push_back(a_pBullet);

	// set rotating to true
	m_bRotating = true;
}

void Target::Rotate() 
{
	if (!m_bRotating)
		return;

	// rotate by angular velocity
	SetModelMatrix(glm::rotate(GetModelMatrix(), m_fAngVelocity, AXIS_X));

	// rotate bullets attached
	for (uint i = 0; i < m_lBulletsStuck.size(); i++)
	{
	
		// position the bullets so are "stuck" in the target and rotate with it
		m_lBulletsStuck[i]->SetModelMatrix(
			glm::translate(GetModelMatrix(), m_fRadii[i] * AXIS_Y + (m_fOrientations[i] * 0.025f + 0.015f) * AXIS_Z) * 
			(m_fOrientations[i] == -1.0f ? glm::rotate(static_cast<float>(PI), AXIS_Y) : IDENTITY_M4)
		);
	}

	m_fOrientationX += m_fAngVelocity;



	// divide angular velocity / 2
	m_fAngVelocity /= 1.2f;

	// if division is less than certain amount, set velocity to 0 & rotating to false
	if (abs(m_fAngVelocity) < 0.001f)
	{
		m_fAngVelocity = 0.0f;
		m_bRotating = false;
	}

}

vector3 Target::GetPivotGlobal()
{
	return vector3(
		GetModelMatrix() * vector4(m_v3Pivot, 1.0f)
	);
}

