#include "main.h"
#include "texture.h"
#include "renderer.h"
#include "game_object.h"
#include "model.h"
#include "scene.h"
#include "manager.h"
#include "bullet.h"
#include "enemy.h"
#include "field.h"


void CBullet::Init()
{
	m_Model = new CModel;
	circle = new CIRCLE;
	m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	circle->radius = BULLET_RADIUS;

	m_Model->Load("asset/miku_01.obj");
}

void CBullet::Draw()
{
	// マトリクス設定
	XMMATRIX world;
	world = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	CRenderer::SetWorldMatrix(&world);
	m_Model->Draw();
}

void CBullet::Uninit()
{
	m_Model->Unload();
}

void CBullet::Update()
{

	////////////////////////////////////////////////////////////
	////		弾の移動
	////////////////////////////////////////////////////////////
	m_Position.x += g_front.x;
	//m_Position.y += g_front.y;
	m_Position.z += g_front.z;
	m_Rotation.y += 0.01f;
	circle->Pos = m_Position;

	if (m_Position.z > 30.0f)
	{
		CManager::GetScene()->DestroyGameObject(this);
	}

	////////////////////////////////////////////////////////////
	////		当たり判定
	////////////////////////////////////////////////////////////
	std::vector<CEnemy*> enemys;
	enemys = CManager::GetScene()->GetGameObjects<CEnemy>(Layer3D_MODEL);
	for (CEnemy* enemy : enemys)
	{
		XMFLOAT3 enemyPos = enemy->GetPosition();
		//if (this->m_Position.x - 1 <= enemyPos.x && this->m_Position.x + 1 >= enemyPos.x && this->m_Position.z-1<= enemyPos.z &&this->m_Position.z+1<=enemyPos.z)
		if(Collision_IsHitCircle(enemy->circle,circle))
		{
			
			CManager::GetScene()->DestroyGameObject(enemy);
			CManager::GetScene()->DestroyGameObject(this);
			return;
		}
	}

	//CField* m_Field = CManager::GetScene()->GetGameObject<CField>(1);
	//m_Position.y = m_Field->GetHeight(m_Position) + 0.5f;
}

void CBullet::SetPosition(XMFLOAT3 position, XMFLOAT3 front)
{
	m_Position = position;
	g_front = front;
}