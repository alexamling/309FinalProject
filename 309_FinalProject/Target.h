/*----------------------------------------------
Programmer: Andrew Schwartz (aes7176@rit.edu)
Date: 2019/04
----------------------------------------------*/

#ifndef __TARGETCLASS_H_
#define __TARGETCLASS_H_

#include "Simplex/Simplex.h"
#include "Bullet.h"
#include "MyEntityManager.h"

namespace Simplex
{

class Target : virtual public MyEntity
{
	//MyRigidBody* m_pTargetRB;

public:
	Target();
	~Target();

//private:
//	void Init();
//	void Release();
};

}

#endif //__TARGETCLASS_H_

