#ifndef WALL_H_
#define WALL_H_

class CShader;
class CWall : public CGameObject
{
private:
	CShader* m_Shader;
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