#include "main.h"
#include "renderer.h"
#include "game_object.h"
#include "scene.h"
#include "manager.h"
#include "bullet_billboard.h"
#include "bullet.h"
#include "stb-texture.h"
#include "Shader.h"
#include "camera.h"

struct sort_asc {
	bool operator()(CGameObject* lhs, CGameObject* rhs) {
		if(rhs != nullptr)
		return dynamic_cast<CBullet_Billboard*>(lhs)->GetSortLenght() > dynamic_cast<CBullet_Billboard*>(rhs)->GetSortLenght();
	}
};

void CBullet::Init()
{
	circle = new CIRCLE;
	m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(0.2f, 0.2f, 0.2f);
	circle->radius = g_kBulletCircleSize;
}


void CBullet::Uninit()
{
}

void CBullet::Update()
{
	////////////////////////////////////////////////////////////
	////		弾の移動
	////////////////////////////////////////////////////////////

	m_Position = XMFLOAT3(m_Position.x + m_front.x * m_kBulletSpeed, m_Position.y + m_front.y * m_kBulletSpeed, m_Position.z + m_front.z * m_kBulletSpeed);

	circle->Pos = m_Position;

	CScene* scene = CManager::GetScene();
	CBullet_Billboard* billborad = scene->AddGameObject<CBullet_Billboard>(Layer3D_BULLET);
	billborad->Bill_Create(m_Position,m_Texture);
	//list.push_back(billborad);

	//list.erase(
	//	std::remove_if(list.begin(), list.end(),
	//		[](CGameObject* object){return object ==nullptr; }),
	//	list.end()
	//);

	//auto itr = list.begin();
	//while (list.end() != itr)
	//{
	//	auto u_itr = *itr;
	//	if (u_itr == nullptr)
	//	{
	//		list.erase(itr);
	//		continue;
	//	}
	//	itr++;
	//}

	/*list.sort(sort_asc());
	CManager::GetScene()->SetSortList(list);*/
	
	//画面外チェック
	if (m_Position.z > 30.0f || m_Position.z < -30.0f || m_Position.x > 30.0f || m_Position.x < -30.0f || m_Position.y > 30.0f || m_Position.y < -30.0f)
	{
		CManager::GetScene()->DestroyGameObject(this);
	}

}

void CBullet::Draw()
{
}

void CBullet::SetBullet(CStbTexture* texture, XMFLOAT3 Position, XMFLOAT3 vec)
{
	m_Texture = texture;
	m_Position = Position;
	m_front = vec;
}