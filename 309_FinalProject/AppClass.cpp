#include "AppClass.h"
using namespace Simplex;
void Application::InitVariables(void)
{
	//Set the position and target of the camera
	m_pCameraMngr->SetPositionTargetAndUpward(
		vector3(0.0f, 0.0f, 100.0f), //Position
		vector3(0.0f, 0.0f, 99.0f),	//Target
		AXIS_Y);					//Up

	m_pLightMngr->SetPosition(vector3(0.0f, 3.0f, 13.0f), 1); //set the position of first light (0 is reserved for ambient light)

#ifdef DEBUG
	uint uInstances = 900;
#else
	uint uInstances = 1849;
#endif
	int nSquare = static_cast<int>(std::sqrt(uInstances));
	m_uObjects = nSquare * nSquare;
	uint uIndex = -1;
	for (int i = 0; i < nSquare; i++)
	{
		for (int j = 0; j < nSquare; j++)
		{
			uIndex++;
			m_pEntityMngr->AddEntity("Minecraft\\Cube.obj");
			vector3 v3Position = vector3(glm::sphericalRand(34.0f));
			matrix4 m4Position = glm::translate(v3Position);
			m_pEntityMngr->SetModelMatrix(m4Position);
		}
	}
	m_uOctantLevels = 3;
	m_pRoot = new MyOctant(m_uOctantLevels, 5);
	m_pGun = new Model();
	m_pGun->Load("Minecraft\\revolver.fbx");
	
	m_pEntityMngr->Update();


}
void Application::Update(void)
{
	/*matrix4 mGun = glm::translate(m_pCameraMngr->GetForward()*1.5f)*glm::scale(vector3(0.1f));*/
	//matrix4 orientation = m_pCameraMngr->GetViewMatrix()*vector4(m_pCameraMngr->GetForward(),1.0f);
	//matrix4 mGun = glm::translate(m_pCameraMngr->GetPosition(0)+m_pCameraMngr->GetForward()*0.75f-vector3(0.0f,0.3f,0.0f))*glm::rotate(m_pCameraMngr->GetViewMatrix(),0.0f,m_pCameraMngr->GetForward());
	//matrix4 mGun = glm::rotate(m_pCameraMngr->GetViewMatrix(), 0.0f, m_pCameraMngr->GetForward());
	//matrix4 mGun = glm::translate(m_pCameraMngr->GetViewMatrix(), m_pCameraMngr->GetForward()*5.0f);
	vector3 v3Sideways = glm::normalize(glm::cross(m_pCameraMngr->GetForward(), AXIS_Y)); // TODO: add a player class that calculates this automatically
	matrix4 mGun = glm::translate(m_pCameraMngr->GetPosition() + m_pCameraMngr->GetForward() * 3.0f + v3Sideways * 1.5f - AXIS_Y) * 
		glm::rotate<float>(matrix4(glm::transpose(matrix3(m_pCameraMngr->GetViewMatrix()))), static_cast<float>(-PI/2.0f), AXIS_Y) * 
		glm::scale(vector3(5.0f));
	m_pGun->SetModelMatrix(mGun);
	m_pMeshMngr->AddAxisToRenderList(mGun);
	m_pGun->AddToRenderList();
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the ArcBall active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();
	
	//Update Entity Manager
	m_pEntityMngr->Update();

	//Add objects to render list
	m_pEntityMngr->AddEntityToRenderList(-1, true);
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	//display octree
	m_pRoot->Display();
	
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