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
	//m_pTargetRB = pRigidBody;
}

//void Simplex::Target::Init() {}
//
//// usually neither of these methods will run, but they're not necessary
Target::~Target()
{ 
	//Release(); 
}

//void Simplex::Target::Release()
//{
//	//m_pTargetRB = nullptr;
//}
