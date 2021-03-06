#include "AppClass.h"
using namespace Simplex;
void Application::InitVariables(void)
{
	Simplex::MeshManager::GetInstance();
	m_pPlayer = new Player(m_pCameraMngr->GetCamera(-1));
	m_pLightMngr->SetPosition(vector3(0.0f, 3.0f, 13.0f), 1); //set the position of first light (0 is reserved for ambient light)
	m_soundBGM.openFromFile("Data/Audio/BigMarty.wav");
	m_soundBGM.setVolume(70.0f);
	m_soundBGM.play();
	

	uint uInstances = 100;
	int nSquare = static_cast<int>(std::sqrt(uInstances));
	m_uObjects = nSquare * nSquare;
	uint uIndex = -1;
	for (int i = 0; i < nSquare; i++)
	{
		for (int j = 0; j < nSquare; j++)
		{
			uIndex++;
			m_pEntityMngr->AddEntity(new Target());
			float distributionAngle = PI / m_uObjects * 2 * (j + nSquare * i);
			vector2 circlePos = vector2(cos(distributionAngle)*25.0f, sin(distributionAngle)*25.0f);
			vector3 v3position = vector3(circlePos.x,-1.5f, circlePos.y);
			float angle=PI-distributionAngle+PI/2.0f;
			matrix4 m4position = glm::rotate(glm::translate(v3position),angle,AXIS_Y);
			m_pEntityMngr->SetModelMatrix(m4position);
		}
	}
	m_uOctantLevels = 3;
	m_pRoot = new MyOctant(m_uOctantLevels, 5);
	m_pGun = new Model();
	m_pGun->Load("Minecraft\\revolver.fbx");
	//m_pBullet = new Model();
	//m_pBullet->Load("Minecraft\\bullet4.fbx");
	m_v3Bullet = new Bullet(m_pCameraMngr->GetCamera(-1)->GetForward(),m_pCameraMngr->GetCamera(-1)->GetCameraSpaceAdjusted());
	m_pEntityMngr->AddBullet(m_v3Bullet);

	m_pPlayer->SetGun(m_pGun);
}
void Application::Update(void)
{
	// updates player and camera and bullet and center ref
	m_pPlayer->Update();
	//m_pBullet->SetModelMatrix(m_pCameraMngr->GetCameraSpaceAdjusted());
	//m_pBullet->AddToRenderList();

	//m_v3Bullet->Update();
	m_pMeshMngr->AddCubeToRenderList(glm::scale(vector3(200.0f, 1.0f, 200.0f))*glm::translate(vector3(0.0f, -2.0f, 0.0f)), vector3(0.96f, 0.87f, 0.70f)); // as reference for movement
	//m_pMeshMngr->AddCubeToRenderList(glm::scale(vector3(5.0f)), C_GREEN);

	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the ArcBall active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();
	
	//Update Entity Manager
	m_pEntityMngr->UpdateBullets();
	m_pRoot->UpdateBulletDimensions();
	m_pEntityMngr->UpdateCollisions();
	m_pEntityMngr->UpdateTargets();

	//Add objects to render list
	m_pEntityMngr->AddEntityToRenderList(-1);
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	//display octree
	m_pRoot->Display(Simplex::vector3(1.0, 0, 0));
	
	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();
	
	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();
	
	//draw gui,
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	SafeDelete(m_pGun);
	delete m_pRoot;
	m_pRoot = nullptr;

	//release GUI
	ShutdownGUI();
}