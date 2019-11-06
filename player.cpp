#include "main.h"
#include "game_object.h"
#include "texture.h"
#include "renderer.h"
#include "input.h"
#include "audio_clip.h"
#include "model.h"
#include "field.h"
#include "scene.h"
#include "manager.h"
#include "player.h"
#include "bullet.h"

static float MoveSpeed = 0.1f;
static float RotationSpeed = 0.1f;




void CPlayer::Init()
{
	m_Model = new CModel();
	m_AudioClip = new CAudioClip();
	m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);


	m_Model->Load("asset/miku_01.obj");
	m_AudioClip->Load("asset/sound/SE/shotsound_001.wav");

}

void CPlayer::Draw()
{
	// マトリクス設定
	XMMATRIX world;
	world = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	CRenderer::SetWorldMatrix(&world);
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_Model->Draw();
}

void CPlayer::Update()
{

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


	///////////////////////////////////////////////////////
	////				回 転
	///////////////////////////////////////////////////////
	//if (GetKeyState('Q') & 0x8000) {
	//	// Qキーが押されている時の処理
	//	m_Rotation.y -= RotationSpeed;

	//	XMVECTOR vec;
	//	XMMATRIX mtx;
	//	mtx = XMMatrixRotationY(-RotationSpeed);
	//	vec = XMVector3TransformNormal(XMLoadFloat3(&g_front), mtx);
	//	XMStoreFloat3(&g_front, vec);

	//	mtx = XMMatrixRotationY(-RotationSpeed);
	//	vec = XMVector3TransformNormal(XMLoadFloat3(&g_right), mtx);
	//	XMStoreFloat3(&g_right, vec);
	//}
	//if (GetKeyState('E') & 0x8000) {
	//	// Eキーが押されている時の処理
	//	m_Rotation.y += RotationSpeed;

	//	XMVECTOR vec;
	//	XMMATRIX mtx;
	//	mtx = XMMatrixRotationY(RotationSpeed);
	//	vec = XMVector3TransformNormal(XMLoadFloat3(&g_front), mtx);
	//	XMStoreFloat3(&g_front, vec);

	//	mtx = XMMatrixRotationY(RotationSpeed);
	//	vec = XMVector3TransformNormal(XMLoadFloat3(&g_right), mtx);
	//	XMStoreFloat3(&g_right, vec);
	//}

	if (CInput::GetKeyTrigger(WM_LBUTTONDOWN))//マウス左クリックWM_LBUTTONDOWN
	{
		CScene* scene = CManager::GetScene();
		CBullet* bullet = scene->AddGameObject<CBullet>(Layer3D_MODEL);
		//float x = scene->player->m_Position.x;
		bullet->SetPosition(m_Position,g_front);
		m_AudioClip->Play();
	}

	CField* m_Field = CManager::GetScene()->GetGameObject<CField>(1);
	m_Position.y = m_Field->GetHeight(m_Position) + 0.5f;
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
	m_Model->Unload();
}