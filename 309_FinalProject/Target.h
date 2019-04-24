/*----------------------------------------------
Programmer: Andrew Schwartz (aes7176@rit.edu)
Date: 2019/04
----------------------------------------------*/

#ifndef __TARGETCLASS_H_
#define __TARGETCLASS_H_

#include "Simplex/Simplex.h"
#include "Bullet.h"
#include "MyEntityManager.h"

#define MAX_TIME 20.0f

namespace Simplex
{

class Target : public MyEntity
{
private:
	static float Target::m_fTimer;
	static float Target::m_fDeltaTime;

public:
	Target();
	~Target();

	static void UpdateTimer(float a_fDeltaTime);
	void Rotate();

};

}

#endif //__TARGETCLASS_H_

