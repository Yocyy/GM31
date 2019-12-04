#include "main.h"
#include "texture.h"
#include "renderer.h"
#include "manager.h"
#include "game_object.h"
#include "BulletManager.h"
#include "stb-texture.h"
#include "bullet.h"
#include "camera.h"
#include "scene.h"

void CBulletManager::Init()
{
	const char* TexFiles[g_kBulletTexNum] = {
		"asset/bullet.tga",
		"asset/bullet.tga",
	};

	for (int i = 0; i < g_kBulletTexNum; i++)
	{
		m_Texture.push_back(new CStbTexture());
		m_Texture[i]->Load(TexFiles[i]);
	}
}

void CBulletManager::Uninit()
{
	for (auto i : m_Texture)
	{
		i->Unload();
		delete i;
	}
}

void CBulletManager::BulletDestroy()
{

}

void CBulletManager::AllBulletDestroy()
{

}

void CBulletManager::CreateBullet(XMFLOAT3 Position, XMFLOAT3 vec, BULLET_TYPE type)
{
	scene = CManager::GetScene();
	CCamera* m_Camera = scene->GetGameObject<CCamera>(Layer3D_CAMERA);
	XMFLOAT4X4* ss = (XMFLOAT4X4*)&m_Camera->Get_Camera_InvViewMatrix();

	vec.x = ss->_31;	//s—ñ‚Ì31,32,33‚ÅCamera‚ÌZForward,41,42,43‚ÅCamera‚ÌPosition
	vec.y = ss->_32;
	vec.z = ss->_33;
	Position.x = ss->_41;
	Position.y = ss->_42;
	Position.z = ss->_43;

	assert(type != BULLET_TYPE::MIN || type != BULLET_TYPE::MAX);//error check
	
	m_Bullet = scene->AddGameObject<CBullet>(Layer3D_EFFECT);
	m_Bullet->SetBullet(m_Texture[static_cast<unsigned int>(type)], Position, vec);

	//list.push_back(m_Bullet);
}
