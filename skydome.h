#pragma once

typedef struct
{
	XMFLOAT3 Pos;
	XMFLOAT3 NVect;
	XMFLOAT2 uv;
}SKYMESH;

class CShader;
class CSkydome : public CGameObject
{
private:
	CShader* m_Shader;
	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11Buffer* m_IndexBuffer = NULL;
	CStbTexture* m_Texture;
	VERTEX_3D* pVertex;

	float radius;
	int surface_num;
	float spin = 0.0f;
	int g_Vertex_max;
	int g_Index_max;
	XMMATRIX View;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};