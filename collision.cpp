#include "collision.h"

bool Collision_IsHitCircle(const CIRCLE* PointerA, const CIRCLE* PointerB)
{
	// A��B�̔��a�𑫂�
	float RadiusAandB = PointerA->radius + PointerB->radius;

	// ��L�̒��������߂�
	float L2 =
		(PointerA->Pos.x - PointerB->Pos.x) * (PointerA->Pos.x - PointerB->Pos.x)
		+ (PointerA->Pos.y - PointerB->Pos.y) * (PointerA->Pos.y - PointerB->Pos.y)
		+ (PointerA->Pos.z - PointerB->Pos.z) * (PointerA->Pos.z - PointerB->Pos.z);


	return (RadiusAandB * RadiusAandB) > L2;
}