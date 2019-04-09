#include "Bullet.h"


Bullet::Bullet() : MyEntity("data\MOBJ\Bullet.obj","bullet")
{

}


Bullet::~Bullet()
{

}

void Bullet::Update()
{
	vector3 pos = GetRigidBody()->GetCenterGlobal();
	
}
