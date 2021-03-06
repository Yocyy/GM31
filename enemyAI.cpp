#include "main.h"
#include "stb-texture.h"
#include "renderer.h"
#include "game_object.h"
#include "model.h"
#include "manager.h"
#include "scene.h"
#include "camera.h"
#include "field.h"
#include "enemyAI.h"
#include "player.h"
#include "Shader.h"


void CEnemyAI::Init()
{
	m_Quaternion = XMQuaternionIdentity();
	circle = new CIRCLE;
	m_Model = new CModel;
	flag_move = false;
	m_Position = XMFLOAT3(0.0f, 1.0f, 5.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);	//float(rand() % 10)
	m_Scale = XMFLOAT3(2.0f, 2.0f, 2.0f);

	//	当たり判定
	circle->radius = m_kHitCircleSize;

	m_Model->Load("asset/miku_01.obj");

	m_Shader = new CShader();
	m_Shader->Init(VS_CSO::Shader_3D, PS_CSO::Shader_3D);
}

void CEnemyAI::Draw()
{
	CCamera* camera;
	camera = CManager::GetScene()->GetGameObject<CCamera>(Layer3D_CAMERA);
	if (camera->GetVisibility(m_Position, m_kHitCircleSize) == false)
	{
		return;
	}

	// マトリクス設定
	XMMATRIX world;
	world = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world *= XMMatrixRotationQuaternion(m_Quaternion);
	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

	XMFLOAT4X4 world4x4;
	XMStoreFloat4x4(&world4x4, world);
	m_Shader->SetWorldMatrix(&world4x4);
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	XMFLOAT4X4 viewmatrix4x4;
	XMStoreFloat4x4(&viewmatrix4x4, camera->Get_Camera_ViewMatrix());
	m_Shader->SetViewMatrix(&viewmatrix4x4);

	XMFLOAT4X4 promatrix4x4;
	XMStoreFloat4x4(&promatrix4x4, camera->Get_Camera_Projection());
	m_Shader->SetProjectionMatrix(&promatrix4x4);

	m_Shader->SetCameraPosition(&camera->Get_Camera_Position4f());

	m_Shader->Set();
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_Model->Draw();
}

XMFLOAT3 CEnemyAI::GetPosition()
{
	return m_Position;
}

void CEnemyAI::Uninit()
{
	m_Model->Unload();
}

void CEnemyAI::Update()
{
	if (moveflag) {
		CPlayer* m_Player = CManager::GetScene()->GetGameObject<CPlayer>(Layer3D_MODEL);
		XMFLOAT3 vec;
		vec.x = m_Player->Get_Player_Position().x - m_Position.x;
		vec.y = m_Player->Get_Player_Position().y - m_Position.y;
		vec.z = m_Player->Get_Player_Position().z - m_Position.z;
		m_Position.x += vec.x * MoveSpeed;
		m_Position.y += vec.y * MoveSpeed;
		m_Position.z += vec.z * MoveSpeed;
	}

	CField* m_Field = CManager::GetScene()->GetGameObject<CField>(Layer3D_MODEL);
	m_Position.y = m_Field->GetHeight(m_Position) + 0.5f;
	circle->Pos = m_Position;
}