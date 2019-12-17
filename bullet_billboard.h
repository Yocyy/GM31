#pragma once

typedef struct BILLBOARD_tag {
	XMFLOAT3 Position;
	int Animation_Count;
}BILLBOARD;

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
	float MoveSpeed = 0.0f;
	int Count;
	XMFLOAT3 m_Front;
public:
	void Bill_Create(XMFLOAT3 Position, XMFLOAT3 Front, float Speed, CStbTexture* StbTexture);
	void Init();
	void Uninit();
	void Update();
	void Draw();
};
