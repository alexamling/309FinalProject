/*----------------------------------------------
Programmer: Andrew Schwartz (aes7176@rit.edu)
Date: 2019/04
----------------------------------------------*/

#ifndef __TARGETCLASS_H_
#define __TARGETCLASS_H_

#include "Simplex/Simplex.h"
#include "Bullet.h"
#include "MyEntityManager.h"

#define BULLET_MASS 1.0f
#define TARGET_MASS 5.0f
#define INITIAL_ANGLE PI / 2.0f

namespace Simplex
{

class Target : public MyEntity
{
private:
	vector3 m_v3Pivot;
	float m_fAngVelocity;
	float m_fOrientationX = INITIAL_ANGLE;
	bool m_bRotating;

public:
	Target();
	~Target();
	vector3 GetPivotGlobal();

	void StartRotate(Bullet *a_pBullet);
	void Rotate();

};

}

#endif //__TARGETCLASS_H_

