#include "MyOctant.h"

namespace Simplex
{
	uint Simplex::MyOctant::m_uOctantCount = 0;
	uint Simplex::MyOctant::m_uMaxLevel = 3;
	uint Simplex::MyOctant::m_uIdealEntityCount = 5;

	Simplex::MyOctant::MyOctant(uint a_nMaxLevel, uint a_nIdealEntityCount)
	{
		m_uOctantCount = 1;
		m_uMaxLevel = a_nMaxLevel;
		m_uIdealEntityCount = a_nIdealEntityCount;

		Init();

		m_uLevel = 1;

		std::vector<vector3> vertecies;

		for (int i = 0; i < m_pEntityMngr->GetEntityCount(); i++) {
			MyRigidBody* rb = m_pEntityMngr->GetEntity(i)->GetRigidBody();
			vertecies.push_back(rb->GetMinGlobal());
			vertecies.push_back(rb->GetMaxGlobal());
		}
		MyRigidBody shell = MyRigidBody(vertecies);
		vector3 v3halfWidth = shell.GetHalfWidth();

		vertecies.clear();

		for (int i = 0; i < 3; i++) {
			if (m_fSize < v3halfWidth[i])
				m_fSize = v3halfWidth[i];
		}
		m_fSize *= 2;

		m_v3Center = shell.GetCenterGlobal();
		m_v3Max = m_v3Center + v3halfWidth;
		m_v3Min = m_v3Center - v3halfWidth;

		ConstructTree(m_uMaxLevel);

		for (int i = 0; i < m_pEntityMngr->GetEntityCount(); i++) {
			AddToLeaves(i);
		}
	}

	Simplex::MyOctant::MyOctant(vector3 a_v3Center, float a_fSize, MyOctant* a_pParent)
	{
		Init();
		m_uOctantCount++;
		m_v3Center = a_v3Center;
		m_fSize = a_fSize;
		m_pParent = a_pParent;
		m_uLevel = m_pParent->GetLevel() + 1;
	}

	Simplex::MyOctant::MyOctant(MyOctant const & other)
	{
		m_uID = other.m_uID;
		m_uLevel = other.m_uLevel;
		m_uChildren = other.m_uChildren;

		m_fSize = other.m_fSize;

		m_pMeshMngr = other.m_pMeshMngr;
		m_pEntityMngr = other.m_pEntityMngr;

		m_v3Center = other.m_v3Center;
		m_v3Min = other.m_v3Min;
		m_v3Max = other.m_v3Max;

		m_pParent = other.m_pParent;
		for (uint i = 0; i < 8; i++) {
			m_pChild[i] = other.m_pChild[i];
		}

		m_EntityList = other.m_EntityList;

		m_pRoot = other.m_pRoot;
		m_lChild = other.m_lChild;
	}

	MyOctant & Simplex::MyOctant::operator=(MyOctant const & other)
	{
		if (&other == this) {
			return *this;
		}

		Release();

		return MyOctant(other);
	}

	Simplex::MyOctant::~MyOctant(void)
	{
		Release();
	}

	void Simplex::MyOctant::Swap(MyOctant & other)
	{
		std::swap(m_uID, other.m_uID);
		std::swap(m_uLevel, other.m_uLevel);
		std::swap(m_uChildren, other.m_uChildren);

		std::swap(m_fSize, other.m_fSize);

		std::swap(m_pMeshMngr, other.m_pMeshMngr);
		std::swap(m_pEntityMngr, other.m_pEntityMngr);

		std::swap(m_v3Center, other.m_v3Center);
		std::swap(m_v3Min, other.m_v3Min);
		std::swap(m_v3Max, other.m_v3Max);

		std::swap(m_pParent, other.m_pParent);
		std::swap(m_pChild, other.m_pChild);

		std::swap(m_EntityList, other.m_EntityList);

		std::swap(m_pRoot, other.m_pRoot);
		std::swap(m_lChild, other.m_lChild);
	}

	float Simplex::MyOctant::GetSize(void)
	{
		return m_fSize;
	}

	uint Simplex::MyOctant::GetLevel() {
		return m_uLevel;
	}

	vector3 Simplex::MyOctant::GetCenterGlobal(void)
	{
		return m_v3Center;
	}

	vector3 Simplex::MyOctant::GetMinGlobal(void)
	{
		return m_v3Min;
	}

	vector3 Simplex::MyOctant::GetMaxGlobal(void)
	{
		return m_v3Max;
	}

	bool Simplex::MyOctant::IsColliding(uint a_uRBIndex)
	{
		MyRigidBody* rb = m_pEntityMngr->GetRigidBody(a_uRBIndex);
		
		bool colliding = true;

		vector3 otherMin = rb->GetMinGlobal();
		vector3 otherMax = rb->GetMaxGlobal();

		if (otherMin.x > m_v3Center.x + (m_fSize * 0.5f))
			colliding = false;

		if (otherMax.x < m_v3Center.x - (m_fSize * 0.5f))
			colliding = false;

		if (otherMin.y > m_v3Center.y + (m_fSize * 0.5f))
			colliding = false;

		if (otherMax.y < m_v3Center.y - (m_fSize * 0.5f))
			colliding = false;

		if (otherMin.z > m_v3Center.z + (m_fSize * 0.5f))
			colliding = false;

		if (otherMax.z < m_v3Center.z - (m_fSize * 0.5f))
			colliding = false;

		return colliding;
	}

	void Simplex::MyOctant::AddToLeaves(uint a_uRBIndex) {
		if (IsLeaf()) {
			AssignIDtoEntity(a_uRBIndex);
		}
		else {
			for (int i = 0; i < 8; i++) {
				if (m_pChild[i]->IsColliding(a_uRBIndex)) {
					m_pChild[i]->AddToLeaves(a_uRBIndex);
				}
			}
		}
	}

	void Simplex::MyOctant::Display(uint a_nIndex, vector3 a_v3Color)
	{

	}

	void Simplex::MyOctant::Display(vector3 a_v3Color)
	{
		for (int i = 0; i < m_uChildren; i++) {
			m_pChild[i]->Display(a_v3Color);
		}
		m_pMeshMngr->AddWireCubeToRenderList(glm::translate(IDENTITY_M4, m_v3Center) * glm::scale(vector3(m_fSize)), a_v3Color);
	}

	void Simplex::MyOctant::DisplayLeafs(vector3 a_v3Color)
	{

	}

	void Simplex::MyOctant::ClearEntityList(void)
	{
		m_EntityList.clear();
	}

	void Simplex::MyOctant::Subdivide(void)
	{

	}

	MyOctant * Simplex::MyOctant::GetChild(uint a_nChild)
	{
		return m_pChild[a_nChild];
	}

	MyOctant * Simplex::MyOctant::GetParent(void)
	{
		return m_pParent;
	}

	bool Simplex::MyOctant::IsLeaf(void)
	{
		return m_uChildren == 0;
	}

	bool Simplex::MyOctant::ContainsMoreThan(uint a_nEntities)
	{
		return sizeof(m_EntityList) > a_nEntities;
	}

	void Simplex::MyOctant::KillBranches(void)
	{
		if (IsLeaf())
			return;

		for (int i = 0; i < 8; i++) {
			m_pChild[i]->KillBranches();
			SafeDelete(m_pChild[i]);
			m_pChild[i] = nullptr;
		}
	}

	void Simplex::MyOctant::ConstructTree(uint a_nMaxLevel)
	{
		if (m_uLevel >= a_nMaxLevel) {
			return;
		}

		float newSize = m_fSize * .5f;
		float centerOffset = m_fSize * .25f;
		m_uChildren = 8;
		vector3 newCenter;
		
		// construct the 8 children
		// right, up, forward
		newCenter = m_v3Center + vector3(centerOffset, centerOffset, centerOffset);
		m_pChild[0] = new MyOctant(newCenter, newSize, this);

		// right, up, backward
		newCenter = m_v3Center + vector3(centerOffset, centerOffset, -centerOffset);
		m_pChild[1] = new MyOctant(newCenter, newSize, this);

		// right, down, forward
		newCenter = m_v3Center + vector3(centerOffset, -centerOffset, centerOffset);
		m_pChild[2] = new MyOctant(newCenter, newSize, this);

		// right, down, backward
		newCenter = m_v3Center + vector3(centerOffset, -centerOffset, -centerOffset);
		m_pChild[3] = new MyOctant(newCenter, newSize, this);

		// left, up, forward
		newCenter = m_v3Center + vector3(-centerOffset, centerOffset, centerOffset);
		m_pChild[4] = new MyOctant(newCenter, newSize, this);

		// left, up, backward
		newCenter = m_v3Center + vector3(-centerOffset, centerOffset, -centerOffset);
		m_pChild[5] = new MyOctant(newCenter, newSize, this);

		// left, down, forward
		newCenter = m_v3Center + vector3(-centerOffset, -centerOffset, centerOffset);
		m_pChild[6] = new MyOctant(newCenter, newSize, this);

		// left, down, backward
		newCenter = m_v3Center + vector3(-centerOffset, -centerOffset, -centerOffset);
		m_pChild[7] = new MyOctant(newCenter, newSize, this);

		// continue to build the tree on each of the children
		for (int i = 0; i < 8; i++) {
			m_pChild[i]->ConstructTree(m_uMaxLevel);
		}
	}

	void Simplex::MyOctant::AssignIDtoEntity(uint a_uRBIndex)
	{
		m_pEntityMngr->AddDimension(a_uRBIndex, m_uID);
	}

	uint Simplex::MyOctant::GetOctantCount(void)
	{
		return m_uOctantCount;
	}

	void Simplex::MyOctant::Release(void)
	{
		if (m_uLevel == 0) {
			delete &m_pMeshMngr;
			delete &m_pEntityMngr;
			KillBranches();
		}

		m_pMeshMngr = nullptr;
		m_pEntityMngr = nullptr;

		m_pParent = nullptr;
	}

	void Simplex::MyOctant::Init(void)
	{
		m_uID = m_uOctantCount;
		m_uChildren = 0;

		m_fSize = 0.0f;

		m_pMeshMngr = MeshManager::GetInstance();
		m_pEntityMngr = MyEntityManager::GetInstance();

		m_v3Center = vector3(0.0f);
		m_v3Min = vector3(0.0f);
		m_v3Max = vector3(0.0f);

		m_pParent = nullptr;
		for (int i = 0; i < 8; i++) {
			m_pChild[i] = nullptr;
		}

		m_EntityList = std::vector<uint>();

		m_pRoot = nullptr;
		m_lChild = std::vector<MyOctant*>();
	}

	void Simplex::MyOctant::ConstructList(void)
	{
	}
}