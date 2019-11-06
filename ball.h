#pragma once
#ifndef BALL_H_
#define BALL_H_
#include "collision.h"
#define BALL_RADIUS (1)

class CBall : public CGameObject
{
private:
	CModel* m_Model;
	XMVECTOR m_Quaternion;
	bool flag_move;
	int ModelFrame = 0;
	int Animation = 0;
	float MoveSpeed = 0.05f;
	float RotationSpeed = 0.5f;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	CIRCLE* circle;
};

#endif // !BALL_H_