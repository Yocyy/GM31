#pragma once
#include "collision.h"
#include "game_object.h"
#include "modelAnimation.h"

class CShader;
class CModel;
class CM4A1 : public CGameObject
{
private:
	constexpr static float m_kCircleSize{ 1.0f };

	CShader* m_Shader;
	CModelAnimation* m_Model;
	bool flag_move;
	XMFLOAT3 m_Front;
	float Lenge = 1.2;
	MATERIAL m_Material;
	COLOR		m_Diffuse;
	COLOR		m_SpecularColor;
	COLOR		m_Emission;
	float		m_Shininess;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	XMFLOAT3 GetPosition();
	void SetPosition(XMFLOAT3 position);
	CIRCLE* circle;
};