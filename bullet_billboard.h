#pragma once
#include <stdio.h>
#include <math.h>

class CStbTexture;
class CShader;
class CBullet_Billboard : public CGameObject
{
private:
	CShader* m_Shader;
	ID3D11Buffer* m_VertexBuffer = NULL;
	CStbTexture* m_Texture = NULL;
	XMMATRIX View;
	XMMATRIX invView;
	VERTEX_3D vertex[4];
	float x = 10.0f;
	float y = 10.0f;
	XMFLOAT3 m_Vec;
	float m_VecLen;

	int Count;
	XMFLOAT3 m_Front;

	MATERIAL m_Material;
	COLOR		m_Ambient;
	COLOR		m_Diffuse;
	COLOR		m_SpecularColor;
	COLOR		m_Emission;
	float		m_Shininess;
public:
	void Bill_Create(XMFLOAT3 Position,CStbTexture* StbTexture);
	void Init();
	void Uninit();
	void Update();
	void Draw();
	float GetSortLenght() { return m_VecLen; };
};
