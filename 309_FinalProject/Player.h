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
		Camera* m_pCamera = nullptr;
		Model* m_pGun = nullptr;
		vector3 m_v3Position;

	public:
		Player(Camera* a_pCamera);
		~Player();

		void MoveForward(float a_fDistance = 0.1f);
		void MoveSideways(float a_fDistance = 0.1f);

		vector3 GetPosition();
		void SetPosition(vector3 a_v3Position);

		void SetGun(Model* a_pGun);
		
		void Update();
	private:
		void Init();
		void Release();
	};
}

#endif //__PLAYERCLASS_H_

