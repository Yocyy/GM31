#include "main.h"
#include "stb-texture.h"
#include "renderer.h"
#include "game_object.h"
#include "model.h"
#include "manager.h"
#include "scene.h"
#include "enemy.h"
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
}

void CEnemy::Draw()
{
	// マトリクス設定
	XMMATRIX world;
	world = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	//CRenderer::SetWorldMatrix(&world);
	m_Model->Draw(world);
}

void CEnemy::Uninit()
{
	m_Model->Unload();
	CScene* scene = CManager::GetScene();
	//CEnemy* bullet = scene->AddGameObject<CEnemy>(Layer3D_MODEL);
	//bullet->m_Position = XMFLOAT3(rand()%10, 1.0f, 5.0f);
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