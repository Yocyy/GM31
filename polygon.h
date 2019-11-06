#ifndef POLYGON_H_
#define POLYGON_H_

#include <d3d11.h>
#include "texture.h"

class CPolygon :public CGameObject
{
public:
	ID3D11Buffer* m_VertexBuffer = NULL;
	CTexture* m_Texture = NULL;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void SetTexture(CTexture* texture);
};

#endif // !POLYGON_H_