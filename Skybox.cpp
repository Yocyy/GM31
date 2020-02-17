#include "main.h"
#include "renderer.h"
#include "Shader.h"
#include "stb-texture.h"
#include "Skybox.h"
#include "camera.h"
#include "manager.h"
#include "scene.h"

#include <vector>

void CSkybox::Init()
{

#pragma region cubevertex



	VERTEX_3D vertex[m_kVertexNum];
	
	//front
	vertex[0].Position = XMFLOAT3(-m_kBoxSize, -m_kBoxSize, m_kBoxSize);
	vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[1].Position = XMFLOAT3(-m_kBoxSize, m_kBoxSize, m_kBoxSize);
	vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	vertex[1].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(m_kBoxSize, -m_kBoxSize, m_kBoxSize);
	vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	vertex[2].TexCoord = XMFLOAT2(1.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(m_kBoxSize, m_kBoxSize, m_kBoxSize);
	vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 0.0f);

	//left
	vertex[4].Position = XMFLOAT3(-m_kBoxSize, -m_kBoxSize, -m_kBoxSize);
	vertex[4].Normal = XMFLOAT3(1.0f, 0.0f, 0.0f);
	vertex[4].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[5].Position = XMFLOAT3(-m_kBoxSize, m_kBoxSize, -m_kBoxSize);
	vertex[5].Normal = XMFLOAT3(1.0f, 0.0f, 0.0f);
	vertex[5].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[6].Position = XMFLOAT3(-m_kBoxSize, -m_kBoxSize, m_kBoxSize);
	vertex[6].Normal = XMFLOAT3(1.0f, 0.0f, 0.0f);
	vertex[6].TexCoord = XMFLOAT2(1.0f, 1.0f);

	vertex[7].Position = XMFLOAT3(-m_kBoxSize, m_kBoxSize, m_kBoxSize);
	vertex[7].Normal = XMFLOAT3(1.0f, 0.0f, 0.0f);
	vertex[7].TexCoord = XMFLOAT2(1.0f, 0.0f);

	//right
	vertex[8].Position = XMFLOAT3(m_kBoxSize, -m_kBoxSize, m_kBoxSize);
	vertex[8].Normal = XMFLOAT3(-1.0f, 0.0f, 0.0f);
	vertex[8].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[9].Position = XMFLOAT3(m_kBoxSize, m_kBoxSize, m_kBoxSize);
	vertex[9].Normal = XMFLOAT3(-1.0f, 0.0f, 0.0f);
	vertex[9].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[10].Position = XMFLOAT3(m_kBoxSize, -m_kBoxSize, -m_kBoxSize);
	vertex[10].Normal = XMFLOAT3(-1.0f, 0.0f, 0.0f);
	vertex[10].TexCoord = XMFLOAT2(1.0f, 1.0f);

	vertex[11].Position = XMFLOAT3(m_kBoxSize, m_kBoxSize, -m_kBoxSize);
	vertex[11].Normal = XMFLOAT3(-1.0f, 0.0f, 0.0f);
	vertex[11].TexCoord = XMFLOAT2(1.0f, 0.0f);

	//back
	vertex[12].Position = XMFLOAT3(m_kBoxSize, -m_kBoxSize, -m_kBoxSize);
	vertex[12].Normal = XMFLOAT3(0.0f, 0.0f, 1.0f);
	vertex[12].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[13].Position = XMFLOAT3(m_kBoxSize, m_kBoxSize, -m_kBoxSize);
	vertex[13].Normal = XMFLOAT3(0.0f, 0.0f, 1.0f);
	vertex[13].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[14].Position = XMFLOAT3(-m_kBoxSize, -m_kBoxSize, -m_kBoxSize);
	vertex[14].Normal = XMFLOAT3(0.0f, 0.0f, 1.0f);
	vertex[14].TexCoord = XMFLOAT2(1.0f, 1.0f);

	vertex[15].Position = XMFLOAT3(-m_kBoxSize, m_kBoxSize, -m_kBoxSize);
	vertex[15].Normal = XMFLOAT3(0.0f, 0.0f, 1.0f);
	vertex[15].TexCoord = XMFLOAT2(1.0f, 0.0f);

	//up
	vertex[16].Position = XMFLOAT3(-m_kBoxSize, m_kBoxSize, m_kBoxSize);
	vertex[16].Normal = XMFLOAT3(0.0f, -1.0f, 0.0f);
	vertex[16].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[17].Position = XMFLOAT3(-m_kBoxSize, m_kBoxSize, -m_kBoxSize);
	vertex[17].Normal = XMFLOAT3(0.0f, -1.0f, 0.0f);
	vertex[17].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[18].Position = XMFLOAT3(m_kBoxSize, m_kBoxSize, m_kBoxSize);
	vertex[18].Normal = XMFLOAT3(0.0f, -1.0f, 0.0f);
	vertex[18].TexCoord = XMFLOAT2(1.0f, 1.0f);

	vertex[19].Position = XMFLOAT3(m_kBoxSize, m_kBoxSize, -m_kBoxSize);
	vertex[19].Normal = XMFLOAT3(0.0f, -1.0f, 0.0f);
	vertex[19].TexCoord = XMFLOAT2(1.0f, 0.0f);

	//down
	vertex[20].Position = XMFLOAT3(-m_kBoxSize, -m_kBoxSize, -m_kBoxSize);
	vertex[20].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[20].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[21].Position = XMFLOAT3(-m_kBoxSize, -m_kBoxSize, m_kBoxSize);
	vertex[21].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[21].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[22].Position = XMFLOAT3(m_kBoxSize, -m_kBoxSize, -m_kBoxSize);
	vertex[22].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[22].TexCoord = XMFLOAT2(1.0f, 1.0f);

	vertex[23].Position = XMFLOAT3(m_kBoxSize, -m_kBoxSize, m_kBoxSize);
	vertex[23].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[23].TexCoord = XMFLOAT2(1.0f, 0.0f);

	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(VERTEX_3D) * m_kVertexNum;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = vertex;
		CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
	}

	WORD index[m_kIndexNum]{
		//front
		0, 1, 2,
		2, 1, 3,
		//left
		4, 5, 6,
		6, 5, 7,
		//right
		8, 9, 10,
		10, 9, 11,
		//back
		12, 13, 14,
		14, 13, 15,
		//up
		16, 17, 18,
		18, 17, 19,
		//donw
		20, 21, 22,
		22, 21, 23,
	};

	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(WORD) * m_kIndexNum;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;


		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = index;
		CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_IndexBuffer);
	}

	for (unsigned int i = 0; i< m_kTextureNum;i++)
	{
		m_Texture[i] = new CStbTexture();
	}
	m_Texture[0]->Load("asset/TEXTURE/Sunset_0000.bmp");
	m_Texture[1]->Load("asset/TEXTURE/Sunset_0001.bmp");
	m_Texture[2]->Load("asset/TEXTURE/Sunset_0002.bmp");
	m_Texture[3]->Load("asset/TEXTURE/Sunset_0003.bmp");
	m_Texture[4]->Load("asset/TEXTURE/Sunset_0004.bmp");
	m_Texture[5]->Load("asset/TEXTURE/Sunset_0005.bmp");
	m_Scale = XMFLOAT3(10, 10, 10);
#pragma endregion

	/*ID3D11Resource* texture = NULL;
	ID3D11ShaderResourceView*	m_ShaderResourceView = NULL;

	CreateDDSTextureFromFile(
		CRenderer::GetDevice(), 
		L"skymap.dds",
		&texture,
		&m_ShaderResourceView
	);

	CRenderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_ShaderResourceView);*/


	//CreateDDSTextureFromFileEx(
	//	CRenderer::GetDevice(),
	//	L"asset/TEXTURE/cubemap.dds",
	//	0, 
	//	D3D11_USAGE_DEFAULT, 
	//	D3D11_BIND_SHADER_RESOURCE,
	//	0,
	//	D3D11_RESOURCE_MISC_TEXTURECUBE,
	//	false, 
	//	nullptr, 
	//	&texture,
	//	&m_ShaderResourceView
	//);

	//CreateDDSTextureFromFileEx(
	//	CRenderer::GetDevice(),
	//	CRenderer::GetDeviceContext(),
	//	L"asset/TEXTURE/cubemap.dds",
	//	0,
	//	D3D11_USAGE_DEFAULT, 
	//	D3D11_BIND_SHADER_RESOURCE,
	//	0, 
	//	D3D11_RESOURCE_MISC_TEXTURECUBE,
	//	false, 
	//	nullptr,
	//	&texture);






	m_Shader = new CShader();
	m_Shader->Init(VS_CSO::SkyBox, PS_CSO::SkyBox);

	m_Tex = new CStbTexture();
	m_Tex->Load("asset/TEXTURE/Sunset_0000.bmp");

}

void CSkybox::Uninit()
{
	m_Shader->Uninit();
	delete m_Shader;

	m_VertexBuffer->Release();

	//for (unsigned int i = 0; i < m_kTextureNum; i++)
	//{
	//	m_Texture[i]->Unload();
	//}
	//delete[] m_Texture;
}

void CSkybox::Update()
{
	
}

void CSkybox::Draw()
{
	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	CRenderer::GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	CRenderer::SetSkyBoxTextures(m_Texture);

	CCamera* camera = CManager::GetScene()->GetGameObject<CCamera>(Layer3D_CAMERA);
	XMMATRIX world;
	world = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	world *= XMMatrixTranslation(camera->Get_Camera_Position4f().x, camera->Get_Camera_Position4f().y, camera->Get_Camera_Position4f().z);
	
	XMFLOAT4X4 world4x4;
	XMStoreFloat4x4(&world4x4, world);
	m_Shader->SetWorldMatrix(&world4x4);

	XMFLOAT4X4 view4x4;
	XMStoreFloat4x4(&view4x4, camera->Get_Camera_ViewMatrix());
	m_Shader->SetViewMatrix(&view4x4);

	XMFLOAT4X4 projection;
	XMStoreFloat4x4(&projection, camera->Get_Camera_Projection());
	m_Shader->SetProjectionMatrix(&projection);

	m_Shader->SetCameraPosition(&camera->Get_Camera_Position4f());

	m_Shader->Set();


	// プリミティブトポロジ設定
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// ポリゴン描画
	CRenderer::GetDeviceContext()->DrawIndexed(m_kIndexNum, 0, 0);
}
