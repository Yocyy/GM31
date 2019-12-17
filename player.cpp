#include "main.h"
#include "game_object.h"
#include "stb-texture.h"
#include "renderer.h"
#include "input.h"
#include "audio_clip.h"
#include "model.h"
#include "field.h"
#include "scene.h"
#include "manager.h"
#include "player.h"
#include "BulletManager.h"
#include "Shader.h"
#include "camera.h"

static float MoveSpeed = 0.1f;
static float RotationSpeed = 0.1f;


void CPlayer::Init()
{
	circle = new CIRCLE();
	circle->radius = m_kCircleSize;
	m_Model = new CModel();
	m_AudioClip = new CAudioClip();
	m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	jump_flag = false;
	velocity = XMFLOAT3(0.0f, 0.0f, 0.0f);

	m_Model->Load("asset/miku_01.obj");
	m_AudioClip->Load("asset/sound/SE/shotsound_001.wav");

	m_Shader = new CShader();
	m_Shader->Init(VS_CSO::Shader_3D, PS_CSO::Shader_3D);

}

void CPlayer::Draw()
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

	XMFLOAT4X4 viewmatrix4x4;
	CCamera* camera = CManager::GetScene()->GetGameObject<CCamera>(Layer3D_CAMERA);
	XMStoreFloat4x4(&viewmatrix4x4, camera->Get_Camera_ViewMatrix());
	m_Shader->SetViewMatrix(&viewmatrix4x4);

	XMFLOAT4X4 promatrix4x4;
	XMStoreFloat4x4(&promatrix4x4, camera->Get_Camera_Projection());
	m_Shader->SetProjectionMatrix(&promatrix4x4);

	m_Shader->Set();
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_Model->Draw();
}

void CPlayer::Update()
{
	circle->Pos = m_Position;
	////////////////////////////////////////////////////////
	////				移 動
	////////////////////////////////////////////////////////


	if (CInput::GetKeyPress('W')) {
		// Wキーが押されている時の処理
		m_Position.x += MoveSpeed * g_front.x;
		m_Position.z += MoveSpeed * g_front.z;
	}
	if (CInput::GetKeyPress('S')) {
		// Dキーが押されている時の処理
		m_Position.x -= MoveSpeed * g_front.x;
		m_Position.z -= MoveSpeed * g_front.z;
	}
	if (CInput::GetKeyPress('D')) {
		// Aキーが押されている時の処理
		m_Position.x += MoveSpeed * g_right.x;
		m_Position.z += MoveSpeed * g_right.z;
	}
	if (CInput::GetKeyPress('A')) {
		// Sキーが押されている時の処理
		m_Position.x -= MoveSpeed * g_right.x;
		m_Position.z -= MoveSpeed * g_right.z;
	}

	if (CInput::GetKeyTrigger(WM_LBUTTONDOWN))//マウス左クリックWM_LBUTTONDOWN
	{
		CManager::GetScene()->GetGameObject<CBulletManager>(Layer3D_Manager)->CreateBullet(m_Position, g_front, BULLET_TYPE::zero);
		m_AudioClip->Play();
	}

	// ジャンプ
	if (CInput::GetKeyTrigger(VK_SPACE) && !jump_flag)
	{
		jump_flag = true;
		velocity.y = m_kJumpforce;
	}
	//重力計算(質量×重力)
	velocity.y -= m_kMass * m_kGravite;

	m_Position.y += velocity.y;

	CField* m_Field = CManager::GetScene()->GetGameObject<CField>(Layer3D_MODEL);
	if (m_Position.y < m_Field->GetHeight(m_Position) + 0.5f)
	{
		m_Position.y = m_Field->GetHeight(m_Position) + 0.5f;
		velocity.y = 0.0f;
		jump_flag = false;
	}
}

XMFLOAT3 CPlayer::Get_Player_Position()
{
	return m_Position;
}
XMFLOAT3 CPlayer::Get_Player_Rotation()
{
	return m_Rotation;
}
XMFLOAT3 CPlayer::Get_Player_Front()
{
	return g_front;
}
void CPlayer::Uninit()
{

	m_Shader->Uninit();
	delete m_Shader;
	m_Model->Unload();
}