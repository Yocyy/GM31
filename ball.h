#pragma once
#ifndef BALL_H_
#define BALL_H_
#include "collision.h"
//c++シリアライズ用インクルード
#include "cereal/cereal.hpp"
#include "cereal/archives/json.hpp"
#include <fstream>
#define BALL_RADIUS (1)

struct VECTOR3 {
	float x, y, z;
	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(
			CEREAL_NVP(x),
			CEREAL_NVP(y),
			CEREAL_NVP(z)
		);
	}
};

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