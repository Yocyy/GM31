#ifndef WALL_H_
#define WALL_H_

class CWall : public CGameObject
{
public:
	ID3D11Buffer* m_VertexBuffer = NULL;
	CStbTexture* m_Texture = NULL;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};

#endif // !WALL_H_