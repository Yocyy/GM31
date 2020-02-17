#pragma once
#include "game_object.h"
class CShader;
class CStbTexture;
class ID3D11Buffer;

typedef struct CubeVertex {
	XMFLOAT3 Position;
	XMFLOAT2 TexCoord;
} CubeVertex;


class CSkybox : public CGameObject {
private:
	int m_kBoxSize = { 10 };
	constexpr static unsigned int m_kVertexNum = { 24 };
	constexpr static unsigned int m_kIndexNum = { 36 };
	constexpr static unsigned int m_kTextureNum = { 6 };
private:
	ID3D11Buffer*	m_VertexBuffer;
	ID3D11Buffer*   m_IndexBuffer;
	CShader*		m_Shader;
	float Rot_Speed = 0.2f;
	CStbTexture*		m_Texture[6] = {};

	CStbTexture* m_Tex;

	ID3D11Buffer* pCubeVB = NULL;
	ID3D11Buffer* pFaceIB = NULL;
	DWORD         hCubeVertexShader = ~0;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};