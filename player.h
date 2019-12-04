#pragma once
#include "collision.h"

class CAudioClip;
class CModel;
class CBulletManager;
class CPlayer : public CGameObject
{
private:
	constexpr static float m_kGravite{ 9.8f };
	constexpr static float m_kMass{ 0.0005f };
	constexpr static float m_kJumpforce{ 0.15f };
	constexpr static float m_kCircleSize{ 1.0f };

	CModel* m_Model;
	CAudioClip* m_AudioClip;
	bool jump_flag;
	XMFLOAT3 velocity;	//‰Á‘¬“x
public:
	XMFLOAT3 g_front = XMFLOAT3(0.0f, 0.0f, 1.0f);
	XMFLOAT3 g_right = XMFLOAT3(1.0f, 0.0f, 0.0f);
	XMFLOAT3 g_up = XMFLOAT3(0.0f, 1.0f, 0.0f);
	void Init();
	void Uninit();
	void Update();
	void Draw();
	XMFLOAT3 Get_Player_Position();
	XMFLOAT3 Get_Player_Rotation();
	XMFLOAT3 Get_Player_Front();
	CIRCLE* circle;
};
