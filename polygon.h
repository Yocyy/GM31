#ifndef POLYGON_H_
#define POLYGON_H_

#include <d3d11.h>

class CStbTexture;
class CShader;
class CPolygon :public CGameObject
{
public:
	CShader* m_Shader;
	ID3D11Buffer* m_VertexBuffer = NULL;
	CStbTexture* m_Texture = NULL;
	float m_Width, m_Height;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void SetTexture(CStbTexture* texture);
};

#endif // !POLYGON_H_