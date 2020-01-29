#include "main.h"
#include "stb-texture.h"
#include "renderer.h"
#include "game_object.h"
#include "model.h"
#include "manager.h"
#include "scene.h"
#include "enemy.h"
#include "Shader.h"
#include "camera.h"
#include <random>

void CEnemy::Init()
{
	circle = new CIRCLE;
	m_Model = new CModelAnimation;
	flag_move = false;
	m_Position = XMFLOAT3(float(rand() % 10), 1.0f, 5.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);	//float(rand() % 10)
	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	circle->radius = m_kCircleSize;

	m_Model->Load("asset/human_2.fbx");//Models/unitychan.fbx

	m_Shader = new CShader();
	m_Shader->Init(VS_CSO::Shader_3D, PS_CSO::Shader_3D);
}

void CEnemy::Draw()
{
	// マトリクス設定
	XMMATRIX world;
	world = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

	XMFLOAT4X4 world4x4;
	XMStoreFloat4x4(&world4x4, world);
	m_Shader->SetWorldMatrix(&world4x4);
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	CCamera* camera;
	camera = CManager::GetScene()->GetGameObject<CCamera>(Layer3D_CAMERA);
	XMFLOAT4X4 viewmatrix4x4;
	XMStoreFloat4x4(&viewmatrix4x4, camera->Get_Camera_ViewMatrix());
	m_Shader->SetViewMatrix(&viewmatrix4x4);

	XMFLOAT4X4 promatrix4x4;
	XMStoreFloat4x4(&promatrix4x4, camera->Get_Camera_Projection());
	m_Shader->SetProjectionMatrix(&promatrix4x4);

	m_Shader->SetCameraPosition(&camera->Get_Camera_Position4f());

	m_Shader->Set();
	m_Model->Draw(world);
}

void CEnemy::Uninit()
{
	m_Model->Unload();

	m_Shader->Uninit();
	delete m_Shader;
}

void CEnemy::Update()
{
	//m_Rotation.y += 0.1f;
	//if (m_Position.x > 7)
	//	flag_move = true;
	//if(flag_move)
	//m_Position.x -= 0.1f;
	//if (m_Position.x < -7)
	//	flag_move = false;
	//if (!flag_move)
	//	m_Position.x += 0.1f;

	//m_Rotation.y += 0.01f;
	circle->Pos = m_Position;
	ModelFrame++;
	m_Model->Update(Animation,ModelFrame);
	if (GetKeyState('T') & 0x8000)
	{
		Animation = 1;
	}
}

XMFLOAT3 CEnemy::GetPosition()
{
	return m_Position;
}