#ifndef COLLISION_H_
#define COLLISION_H_
#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;

typedef struct CIRCLE_tag{
	XMFLOAT3 Pos;
	float radius;
}CIRCLE;

bool Collision_IsHitCircle(const CIRCLE* PointerA, const CIRCLE* PointerB);

#endif // !COLLISION_H_