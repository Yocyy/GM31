#pragma once

#include "game_object.h"

class CShader;
class CStbTexture;
class CPolygon2D : public CGameObject
{
private:

	ID3D11Buffer*	m_VertexBuffer = NULL;
	CShader*		m_Shader;

	CStbTexture*		m_Texture;
	float m_Width, m_Height;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};