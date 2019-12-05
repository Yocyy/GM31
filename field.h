#pragma once

class CField : public CGameObject
{
private:

	ID3D11Buffer*	m_VertexBuffer = NULL;
	ID3D11Buffer*	m_IndexBuffer = NULL;
	CStbTexture*		m_Texture = NULL;


	static const int FIELD_X = 128;
	static const int FIELD_Z = 128;

	VERTEX_3D m_Vertex[FIELD_X * FIELD_Z];
	float size = 1.0f;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	float GetHeight(XMFLOAT3 position);
	XMFLOAT3 OuterProduct(XMFLOAT3 v1, XMFLOAT3 v2);
	float InnerProduct(XMFLOAT3 v1, XMFLOAT3 v2);
};