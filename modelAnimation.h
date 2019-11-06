#ifndef MODELANIMATION_H_
#define MODELANIMATION_H_

#include <map>

struct MESH
{
	ID3D11Buffer* m_VertexBuffer;
	ID3D11Buffer* m_IndexBuffer;
	unsigned int m_IndexNum;
};
class CModelAnimation
{
private:
	MESH* m_Mesh;
	unsigned int m_MeshNum;
	const aiScene* m_Scene[2];
	std::map<std::string, aiQuaternion> m_NodeRotation;
	std::map<std::string, aiVector3D>   m_NodePosition;

public:
	void Draw(XMMATRIX matrix);
	void DrawMesh(aiNode* node, XMMATRIX Matrix);
	void Load(const char* FileName);
	void Unload();
	void Update(int Animation,int Frame);
};
#endif //MODELANIMATION_H_