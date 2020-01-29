#pragma once
#include "game_object.h"

struct ALLLIGHT
{
	XMFLOAT4	Direction;
	XMFLOAT4	Position;
	COLOR		Color;
	float       Pow;
	

	float  Attenuation0;	//àÍíËå∏êäåWêî
	float  Attenuation1;	//ê¸å`å∏êäåWêî
	float  Attenuation2;	//ÇQéüå∏êäåWêî

	UINT		Type;
	XMFLOAT3	 Dummy;
};

class CShader;
class CLightManager : public CGameObject
{
private:
	constexpr static int MAX_LIGHT{ 5 };
	constexpr static int DIRECTION{ 0 };
	constexpr static int POINT{ 1 };
	constexpr static int SPOT{ 2 };
	ALLLIGHT m_Light[MAX_LIGHT];
	ID3D11Buffer* m_LightBuffer;
	float MoveSpeed = 0.5f;
	XMFLOAT3 front = { 0,0,1 };
	XMFLOAT3 right = { 1,0,0 };
	XMFLOAT3 up = { 0,1,0 };
	XMFLOAT4	m_Direction;
	XMFLOAT4	m_Position;
	COLOR		m_Color;
	float		m_Pow;
	float       m_Attenuation0;
	float       m_Attenuation1;
	float       m_Attenuation2;
	UINT		m_Type;

	XMFLOAT4	m_DirLightDirection;
	XMFLOAT4	m_DirLightPosition;
	COLOR		m_DirLightColor;
	float		m_DirLightPow;
	float       m_DirLightAttenuation0;
	float       m_DirLightAttenuation1;
	float       m_DirLightAttenuation2;
	UINT		m_DirLightType;

	XMFLOAT4	m_SpotLightDirection;
	XMFLOAT4	m_SpotLightPosition;
	COLOR		m_SpotLightColor;
	float		m_SpotLightPow;
	float       m_SpotLightAttenuation0;
	float       m_SpotLightAttenuation1;
	float       m_SpotLightAttenuation2;
	UINT		m_SpotLightType;

	float m_RotationSpeed = 0.05f;
	XMFLOAT3 m_Front{0,-1,0};
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void SetDirection(XMFLOAT4 direction) { m_Direction = direction; };
	void SetPos(XMFLOAT4 pos) { m_Position = pos; };
	void SetColor(COLOR color) { m_Color = color; };
	void SetPow(float pow) { m_Pow = pow; };
	void SetType(UINT type) { m_Type = type; };
};