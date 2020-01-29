#pragma once
#include "collision.h"
//c++シリアライズ用インクルード
#include "cereal/cereal.hpp"
#include "cereal/archives/json.hpp"
#include <fstream>

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

class CShader;
class CModel;
class CBall : public CGameObject
{
private:
	constexpr static float m_kCircleSize{ 1.0f };
	CShader* m_Shader;
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
	XMFLOAT3 GetPos() { return m_Position; };
	CIRCLE* circle;
};