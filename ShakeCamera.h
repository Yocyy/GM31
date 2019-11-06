#pragma once
class CShakeCamera
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	static void Shake(float duration, float magnitude, XMFLOAT3* position);
};