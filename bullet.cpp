#include "main.h"
#include "texture.h"
#include "renderer.h"
#include "game_object.h"
#include "model.h"
#include "scene.h"
#include "manager.h"
#include "bullet.h"
#include "enemy.h"
#include "camera.h"
#include "bullet_billboard.h"

void CBullet::Init()
{
	//m_Model = new CModel();
	//m_Model->Load("asset/miku_01.obj");
	circle = new CIRCLE;
	m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(0.2f, 0.2f, 0.2f);
	circle->radius = BULLET_RADIUS;

	Bullet_Speed = 5.0f;



	CCamera* m_Camera = CManager::GetScene()->GetGameObject<CCamera>(Layer3D_CAMERA);
	XMFLOAT4X4* ss = (XMFLOAT4X4*)&m_Camera->Get_Camera_InvViewMatrix();
	g_front.x = ss->_31;	//行列の31,32,33でCameraのZForward,41,42,43でCameraのPosition
	g_front.y = ss->_32;
	g_front.z = ss->_33;
	m_Position.x = ss->_41;
	m_Position.y = ss->_42;
	m_Position.z = ss->_43;


}


void CBullet::Uninit()
{
	//m_Model->Unload();
	//delete m_Model;
	//m_Texture->Unload();
	//delete m_Texture;

	//m_Billboard->Uninit();
	//delete m_Billboard;
}
void CBullet::Update()
{

	////////////////////////////////////////////////////////////
	////		弾の移動
	////////////////////////////////////////////////////////////

	m_Position = XMFLOAT3(m_Position.x + g_front.x * BULLET_SPEED, m_Position.y + g_front.y * BULLET_SPEED, m_Position.z + g_front.z * BULLET_SPEED);

	circle->Pos = m_Position;

	CScene* scene = CManager::GetScene();
	CBullet_Billboard* billborad = scene->AddGameObject<CBullet_Billboard>(Layer2D_UI);
	billborad->Bill_Create(m_Position, g_front, Bullet_Speed, "asset/bullet.tga");
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

	CRenderer::SetWorldMatrix(&world);
	//m_Model->Draw();
}