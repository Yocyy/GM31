#include "main.h"
#include "game_object.h"
#include "ShakeCamera.h"


	float elapsed = 0.0f;
void CShakeCamera::Shake(float duration, float magnitude, XMFLOAT3* position)
{
	XMFLOAT3* pos = position;

	if(elapsed/60 < duration)
	{
	position->x = pos->x + (rand() % 3-1) * magnitude;
	position->y = pos->y + (rand() % 3-1) * magnitude;

	//position = &XMFLOAT3(x, y, pos->z);
	elapsed++;
	}
	else
	position = pos;
}
