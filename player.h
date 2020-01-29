#pragma once
#include "collision.h"

class CAudioClip;
class CModel;
class CBulletManager;
class CShader;
class Weapons;
class CPlayer : public CGameObject
{
private:
	constexpr static float m_kGravite{ 9.8f };
	constexpr static float m_kMass{ 0.0005f };
	constexpr static float m_kJumpforce{ 0.15f };
	constexpr static float m_kCircleSize{ 1.0f };

	CShader* m_Shader;
	CModel* m_Model;
	CScene* m_Scene;
	CAudioClip* m_AudioClip;
	bool jump_flag,scope_flag;
	XMFLOAT3 velocity;	//‰Á‘¬“x

	Weapons* currentWeapon;
	Weapons* nextWeapon;
	Weapons* prevWeapon;
	bool InitFlag = false;

	XMFLOAT3 m_Front = XMFLOAT3(0.0f, 0.0f, 1.0f);
	XMFLOAT3 m_Right = XMFLOAT3(1.0f, 0.0f, 0.0f);
	XMFLOAT3 m_Up = XMFLOAT3(0.0f, 1.0f, 0.0f);
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void Fire();
	void NextWeaponChange();
	void PrevWeaponChange();
	void Reload();
	void Jump();
	XMFLOAT3 Get_Player_Position();
	XMFLOAT3 Get_Player_Rotation();

	XMFLOAT3 Get_Player_Front() { return m_Front; };
	XMFLOAT3 Get_Player_Right() { return m_Right; };
	XMFLOAT3 Get_Player_Up() { return m_Up; };

	void Set_Player_Front(XMFLOAT3 front) { m_Front = front; };
	void Set_Player_Right(XMFLOAT3 right) { m_Right = right; };
	void Set_Player_Up(XMFLOAT3 up) { m_Up = up; };

	CIRCLE* circle;
};
