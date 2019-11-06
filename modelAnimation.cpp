#include "main.h"

#include "renderer.h"
#include "texture.h"
#include "modelAnimation.h"

void CModelAnimation::Draw(XMMATRIX matrix)
{
	DrawMesh(m_Scene[0]->mRootNode, matrix);
}

void CModelAnimation::DrawMesh(aiNode * node, XMMATRIX Matrix)
{
	XMMATRIX world;
	//　回転
	aiQuaternion aiQuat = m_NodeRotation[node->mName.C_Str()];
	XMVECTOR quat = XMLoadFloat4(&XMFLOAT4(aiQuat.x, aiQuat.y, aiQuat.z, aiQuat.w));
	world = XMMatrixRotationQuaternion(quat);
	//　移動
	aiVector3D aiVec = m_NodePosition[node->mName.C_Str()];
	world *= XMMatrixTranslation(aiVec.x, aiVec.y, aiVec.z);


	world *= Matrix;			//親のマトリクスをかけると階層構造

	CRenderer::SetWorldMatrix(&world);
	for (int n = 0; n < node->mNumMeshes; n++)
	{
		unsigned int m = node->mMeshes[n];
		// 頂点バッファ設定
		CRenderer::SetVertexBuffers(m_Mesh[m].m_VertexBuffer);

		// インデックスバッファ設定
		CRenderer::SetIndexBuffer(m_Mesh[m].m_IndexBuffer);

		// ポリゴン描画
		CRenderer::DrawIndexed(m_Mesh[m].m_IndexNum, 0, 0);
	}

	for (int i = 0; i < node->mNumChildren; i++)
	{
		DrawMesh(node->mChildren[i], world);
	}

}

void CModelAnimation::Load(const char * FileName)
{
	m_Scene[0] = aiImportFile(FileName, aiProcessPreset_TargetRealtime_MaxQuality);
	m_Scene[1] = aiImportFile("asset/human_2_handup.fbx", aiProcessPreset_TargetRealtime_MaxQuality);
	m_MeshNum = m_Scene[0]->mNumMeshes;
	m_Mesh = new MESH[m_MeshNum];
	for (int m = 0; m < m_MeshNum; m++)
	{
		aiMesh* mesh = m_Scene[0]->mMeshes[m];
		VERTEX_3D* vertex = new VERTEX_3D[mesh->mNumVertices];
		for (int i = 0; i < mesh->mNumVertices; i++)
		{
			vertex[i].Position = XMFLOAT3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
			vertex[i].Normal = XMFLOAT3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
			vertex[i].Diffuse = XMFLOAT4(1, 1, 1, 1);
			//vertex[i].TexCoord = XMFLOAT2(1, 1);
		}

		// 頂点バッファ生成
		{
			D3D11_BUFFER_DESC bd;
			ZeroMemory(&bd, sizeof(bd));
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.ByteWidth = sizeof(VERTEX_3D) * mesh->mNumVertices;	//バイトのサイズ×頂点数
			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;				//バッファをどのように使うか
			bd.CPUAccessFlags = 0;

			D3D11_SUBRESOURCE_DATA sd;
			ZeroMemory(&sd, sizeof(sd));
			sd.pSysMem = vertex;	//初期化時の先頭アドレス

			CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_Mesh[m].m_VertexBuffer);
		}
		delete[] vertex;

		unsigned short* index;
		index = new unsigned short[mesh->mNumFaces * 3];
		for (int i = 0; i < mesh->mNumFaces; i++)
		{
			index[i * 3 + 0] = mesh->mFaces[i].mIndices[0];
			index[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
			index[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
		}
		m_Mesh[m].m_IndexNum = mesh->mNumFaces * 3;

		// インデックスバッファ生成
		{
			D3D11_BUFFER_DESC bd;
			ZeroMemory(&bd, sizeof(bd));
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.ByteWidth = sizeof(unsigned short) * m_Mesh[m].m_IndexNum;
			bd.BindFlags = D3D11_BIND_INDEX_BUFFER;

			D3D11_SUBRESOURCE_DATA sd;
			ZeroMemory(&sd, sizeof(sd));
			sd.pSysMem = index;	//初期化時の先頭アドレス
			CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_Mesh[m].m_IndexBuffer);
		}
		delete[] index;
	}


}

void CModelAnimation::Unload()
{
	for (int m = 0; m < m_MeshNum; m++)
	{
		m_Mesh[m].m_VertexBuffer->Release();
		m_Mesh[m].m_IndexBuffer->Release();
	}
	delete[] m_Mesh;
	aiReleaseImport(m_Scene[0]);
}

void CModelAnimation::Update(int Animation,int Frame)
{
	aiAnimation* animation = m_Scene[Animation]->mAnimations[0];
	for (int c = 0; c < animation->mNumChannels; c++)
	{
		aiNodeAnim* nodeAnim = animation->mChannels[c];
		int f = Frame % nodeAnim->mNumRotationKeys;
		m_NodeRotation[nodeAnim->mNodeName.C_Str()] =
			nodeAnim->mRotationKeys[f].mValue;
		int g = Frame % nodeAnim->mNumPositionKeys;
		m_NodePosition[nodeAnim->mNodeName.C_Str()] =
			nodeAnim->mPositionKeys[g].mValue;
	}
}
