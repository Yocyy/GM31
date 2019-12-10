#include "main.h"
#include "renderer.h"
#include "game_object.h"
#include "scene.h"
#include "manager.h"
#include "bullet.h"
#include "bullet_billboard.h"
#include "stb-texture.h"
#include "Shader.h"
#include "camera.h"

void CBullet::Init()
{
	circle = new CIRCLE;
	m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(0.2f, 0.2f, 0.2f);
	circle->radius = g_kBulletCircleSize;

	Bullet_Speed = 5.0f;

	m_Shader = new CShader();
	m_Shader->Init(VS_CSO::Shader_3D, PS_CSO::Shader_3D);
}


void CBullet::Uninit()
{
}

void CBullet::Update()
{
	////////////////////////////////////////////////////////////
	////		弾の移動
	////////////////////////////////////////////////////////////

	m_Position = XMFLOAT3(m_Position.x + g_front.x * m_kBulletSpeed, m_Position.y + g_front.y * m_kBulletSpeed, m_Position.z + g_front.z * m_kBulletSpeed);

	circle->Pos = m_Position;

	CScene* scene = CManager::GetScene();
	CBullet_Billboard* billborad = scene->AddGameObject<CBullet_Billboard>(Layer2D_UI);
	billborad->Bill_Create(m_Position, g_front, Bullet_Speed, m_Texture);
	//画面外チェック
	if (m_Position.z > 30.0f || m_Position.z < -30.0f || m_Position.x > 30.0f || m_Position.x < -30.0f || m_Position.y > 30.0f || m_Position.y < -30.0f)
	{
		CManager::GetScene()->DestroyGameObject(this);
	}

}

void CBullet::Draw()
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
}

void CBullet::SetBullet(CStbTexture* texture, XMFLOAT3 Position, XMFLOAT3 vec)
{
	m_Texture = texture;
	m_Position = Position;
	g_front = vec;
}
