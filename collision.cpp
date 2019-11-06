#include "collision.h"

bool Collision_IsHitCircle(const CIRCLE* PointerA, const CIRCLE* PointerB)
{
	// A‚ÆB‚Ì”¼Œa‚ð‘«‚·
	float RadiusAandB = PointerA->radius + PointerB->radius;

	// •ÓL‚Ì’·‚³‚ð‹‚ß‚é
	float L2 =
		(PointerA->Pos.x - PointerB->Pos.x) * (PointerA->Pos.x - PointerB->Pos.x)
		+ (PointerA->Pos.y - PointerB->Pos.y) * (PointerA->Pos.y - PointerB->Pos.y)
		+ (PointerA->Pos.z - PointerB->Pos.z) * (PointerA->Pos.z - PointerB->Pos.z);


	return (RadiusAandB * RadiusAandB) > L2;
}