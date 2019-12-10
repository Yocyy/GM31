#ifndef MESH_FIELD_H_
#define MESH_FIELD_H_
#define FIELD_SIZE (5)

class CShader;
class CMesh_Field :public CGameObject
{
private:
	CShader* m_Shader;
	XMINT3 vertex;
	float g_FieldHeight[5][5] =
	{
		{1.5f,1.5f,1.0f,-1.0f,1.0f},
		{2.5f,1.5f,1.0f,-0.5f,1.0f},
		{3.5f,1.5f,1.0f,-0.5f,1.0f},
		{4.5f,1.5f,1.0f,-0.5f,1.0f},
		{5.5f,1.5f,1.0f,-0.5f,1.0f}
	};
private:
	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11Buffer* m_IndexBuffer = NULL;
	CStbTexture* m_Texture = NULL;
	VERTEX_3D* pVertex;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	float GetHeight(XMFLOAT3 Position);
	XMFLOAT3 OuterProduct(XMFLOAT3 v1, XMFLOAT3 v2);	//äOêœä÷êî
	float InnerProduct(XMFLOAT3 v1, XMFLOAT3 v2);	//ì‡êœä÷êî
};

#endif // !MESH_FIELD_H_

