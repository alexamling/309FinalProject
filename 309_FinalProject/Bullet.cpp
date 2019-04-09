#include "Bullet.h"


Bullet::Bullet() : MyEntity("data\MOBJ\Bullet.obj", "bullet") {
	Bullet(vector3(0));
}

Bullet::Bullet(vector3 a_v3Velocity) : MyEntity("data\MOBJ\Bullet.obj", "bullet")
{
	// TODO: Set model rotation to be in-line with movement
}


Bullet::~Bullet()
{

}

void Bullet::Update()
{
	GetRigidBody()->Move(velocity);
}
