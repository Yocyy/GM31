#include "main.h"
#include "input.h"
#include "fieldNormal.h"
#include "scene.h"
#include "renderer.h"
#include "stb-texture.h"
#include "manager.h"
#include "Camera.h"
#include "shaderNormal.h"

void CFieldNormal::Init()
{
	VERTEX_3D_NORMAL vertex[4];

	vertex[0].Position = XMFLOAT3(0.0f, 5.0f, 0.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Binormal = XMFLOAT3(1.0f, 0.0f, 0.0f);
	vertex[0].Tangent = XMFLOAT3(0.0f, 0.0f, 1.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(5.0f, 5.0f, 0.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Binormal = XMFLOAT3(1.0f, 0.0f, 0.0f);
	vertex[1].Tangent = XMFLOAT3(0.0f, 0.0f, 1.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Binormal = XMFLOAT3(1.0f, 0.0f, 0.0f);
	vertex[2].Tangent = XMFLOAT3(0.0f, 0.0f, 1.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(5.0f, 0.0f, 0.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[3].Binormal = XMFLOAT3(1.0f, 0.0f, 0.0f);
	vertex[3].Tangent = XMFLOAT3(0.0f, 0.0f, 1.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);

	m_Position = XMFLOAT3(10, 0, 0);	//初期値
	m_Rotation = XMFLOAT3(0, 0, 0);

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D_NORMAL) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	m_Texture[0] = new CStbTexture();
	m_Texture[0]->Load("asset/TEXTURE/Rock_Normal.tga");
	m_Texture[1] = new CStbTexture();
	m_Texture[1]->Load("asset/TEXTURE/field004.tga");
	m_Texture[2] = new CStbTexture();
	m_Texture[2]->Load("asset/TEXTURE/Rock_Displacement.tga");

	m_Shader = new CShaderNormal();
	m_Shader->Init("x64/Debug/Shader3DNormalMappingVS.cso", "x64/Debug/Shader3DNormalMappingPS.cso");
}

void CFieldNormal::Uninit()
{
	m_Shader->Uninit();
	delete m_Shader;

	m_VertexBuffer->Release();

	m_Texture[0]->Unload();
	delete m_Texture[0];
	m_Texture[1]->Unload();
	delete m_Texture[1];
	m_Texture[2]->Unload();
	delete m_Texture[2];
}

void CFieldNormal::Update()
{
	//if (CInput::GetKeyPress('W'))
	//{
	//	m_Rotation.x += Rot_Speed;
	//}
	//if (CInput::GetKeyPress('S'))
	//{
	//	m_Rotation.x -= Rot_Speed;
	//}
	//if (CInput::GetKeyPress('D'))
	//{
	//	m_Rotation.y += Rot_Speed;
	//}
	//if (CInput::GetKeyPress('A'))
	//{
	//	m_Rotation.y -= Rot_Speed;
	//}

	//if (CInput::GetKeyPress('I'))
	//{
	//	m_Position.y += Rot_Speed;
	//}
	//if (CInput::GetKeyPress('K'))
	//{
	//	m_Position.y -= Rot_Speed;
	//}

	//if (CInput::GetKeyPress(VK_UP))
	//{
	//	m_Position.z += Rot_Speed;
	//}
	//if (CInput::GetKeyPress(VK_DOWN))
	//{
	//	m_Position.z -= Rot_Speed;
	//}
	//if (CInput::GetKeyPress(VK_RIGHT))
	//{
	//	m_Position.x += Rot_Speed;
	//}
	//if (CInput::GetKeyPress(VK_LEFT))
	//{
	//	m_Position.x -= Rot_Speed;
	//}
}

void CFieldNormal::Draw()
{

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D_NORMAL);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	CRenderer::SetTexture(m_Texture[0], m_Texture[1],m_Texture[2]);

	XMMATRIX world;
	world = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

	XMFLOAT4X4 projection;
	XMFLOAT4X4 matrix;
	DirectX::XMStoreFloat4x4(&projection, XMMatrixPerspectiveFovLH(XM_PI / 2, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 1000.0f));
	XMStoreFloat4x4(&matrix, world);
	m_Shader->SetWorldMatrix(&matrix);
	CCamera* camera = CManager::GetScene()->GetGameObject<CCamera>(Layer3D_CAMERA);
	XMStoreFloat4x4(&matrix, camera->Get_Camera_ViewMatrix());
	m_Shader->SetViewMatrix(&matrix);
	m_Shader->SetProjectionMatrix(&projection);
	m_Shader->SetCameraPosition(&camera->Get_Camera_Position4f());

	m_Shader->Set();


	// プリミティブトポロジ設定
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ポリゴン描画
	CRenderer::GetDeviceContext()->Draw(4, 0);
}

bool CFieldNormal::CheckInput()
{
	//if (CInput::GetKeyPress('W'))
	//{
	//	m_Rotation.y += Rot_Speed;
	//	return true;
	//}
	//if (CInput::GetKeyPress('S'))
	//{
	//	m_Rotation.y -= Rot_Speed;
	//	return true;
	//}
	//if (CInput::GetKeyPress('D'))
	//{
	//	m_Rotation.x += Rot_Speed;
	//	return true;
	//}
	//if (CInput::GetKeyPress('A'))
	//{
	//	m_Rotation.x -= Rot_Speed;
	//	return true;
	//}
	return false;
}
