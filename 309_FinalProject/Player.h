/*----------------------------------------------
Programmer: Andrew Schwartz (aes7176@rit.edu)
Date: 2019/04
----------------------------------------------*/

#ifndef __PLAYERCLASS_H_
#define __PLAYERCLASS_H_

#include "Simplex/Simplex.h"

namespace Simplex {
	class Player
	{
		Camera* m_pCamera = nullptr; // pointer to the camera that the player uses
		Model* m_pGun = nullptr; // pointer to the gun model to use as the viewmodel
		vector3 m_v3Position; // position of player

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

