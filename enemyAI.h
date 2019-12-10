#pragma once

#include "collision.h"

class CShader;
class CEnemyAI : public CGameObject
{
private:
	constexpr static float m_kHitCircleSize{ 5.0f };

	CShader* m_Shader;
	CModel* m_Model;
	XMVECTOR m_Quaternion;
	bool flag_move;
	int ModelFrame = 0;
	int Animation = 0;
	float MoveSpeed = 0.002f;
	float RotationSpeed = 0.5f;
public:
	bool moveflag;
	void Init();
	void Uninit();
	void Update();
	void Draw();
	XMFLOAT3 GetPosition();

	CIRCLE* circle;
};