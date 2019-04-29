/*----------------------------------------------
Programmer: Andrew Schwartz (aes7176@rit.edu)
Date: 2019/04
----------------------------------------------*/

#ifndef __PLAYERCLASS_H_
#define __PLAYERCLASS_H_

#include "Simplex/Simplex.h"
#include "Bullet.h"
#include "MyEntityManager.h"

namespace Simplex {
	class Player
	{
		Camera* m_pCamera = nullptr;
		Model* m_pGun = nullptr;
		vector3 m_v3Position;
		MyEntityManager* m_pEntityMngr = nullptr;
		bool sighted = false;

	public:
		/*
		USAGE: Constructor
		ARGUMENTS: Camera* a_pCamera -> Camera attached to player object
		OUTPUT: ---
		*/
		Player(Camera* a_pCamera);
		/*
		USAGE: Destructor
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		~Player();

		// movement methods

		/*
		USAGE: Moves the player position forward by a specified distance
		ARGUMENTS: float a_fDistance -> Distance the player will move forward
		OUTPUT: ---
		*/
		void MoveForward(float a_fDistance = 0.1f);
		/*
		USAGE: Moves the player position sideways by a specified distance
		ARGUMENTS: float a_fDistance -> Distance the player will move sideways
		OUTPUT: ---
		*/
		void MoveSideways(float a_fDistance = 0.1f);
		/*
		USAGE: Returns the player's position
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		vector3 GetPosition();
		/*
		USAGE: Sets the player position
		ARGUMENTS: a_v3Position -> new position of the player
		OUTPUT: ---
		*/
		void SetPosition(vector3 a_v3Position);

		// viewmodel
		/*
		USAGE: Sets the gun model to use for the player viewmodel
		ARGUMENTS: a_pGun -> pointer to a model (of a gun)
		OUTPUT: ---
		*/
		void SetGun(Model* a_pGun);

		/*
		USAGE: Sets the gun entity to use for the player viewmodel
		ARGUMENTS: a_pGun -> pointer to a model (of a gun)
		OUTPUT: ---
		*/
		void SetGun(MyEntity* a_pGun);
		

		/*
		USAGE: Toggles the boolean that controls ironsights
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		void Ironsights();

		/*
		USAGE: Returns whether or not the gun is sighted
		ARGUMENTS: ---
		OUTPUT: bool sighted
		*/
		bool IsSighted();

		// update methods
		/*
		USAGE: Updates the camera and viewmodel positions
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		void Update();
	private:
		/*
		USAGE: initializes member fields 
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		void Init();
		/*
		USAGE: deallocates member fields
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		void Release();
	};
}

#endif //__PLAYERCLASS_H_

