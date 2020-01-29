#pragma once
#include "game_object.h"
class CShader;
class CStbTexture;
class ID3D11Buffer;

class CSkybox : public CGameObject {
private:
	ID3D11Buffer*	m_VertexBuffer;
	CShader*		m_Shader;
	float Rot_Speed = 0.2f;
	CStbTexture*		m_Texture;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};