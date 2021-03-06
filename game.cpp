#include "main.h"
#include "renderer.h"
#include "audio_clip.h"
#include "game_object.h"
#include "scene.h"
#include "input.h"
#include "result.h"
#include "game.h"
#include "manager.h"
#include "polygon.h"
#include "wall.h"
#include "mesh_field.h"
#include "field.h"
#include "player.h"
#include "camera.h"
#include "enemy.h"
#include "bullet.h"
#include "ball.h"
#include "judgement.h"
#include "BulletManager.h"
#include "enemyAI.h"
#include "DirectionalLight.h"
#include "LightManager.h"
#include "m4a1.h"
#include "fieldNormal.h"
#include "skydome.h"
#include "polygon2D.h"
#include "WeaponState.h"
#include "Skybox.h"

static bool flag_result;

void CGame::Init()
{
	ShowCursor(false);
	AddGameObject<CLightManager>(Layer3D_LIGHT);
	AddGameObject<CBulletManager>(Layer3D_Manager);
	AddGameObject<CCamera>(Layer3D_CAMERA);
	AddGameObject<CJudgement>(Layer3D_CAMERA);
	//AddGameObject<CBall>(Layer3D_MODEL);
	AddGameObject<CField>(Layer3D_MODEL);
	AddGameObject<CWall>(Layer3D_MODEL);

	AddGameObject<KNIFE>(Layer3D_MODEL);
	AddGameObject<AK>(Layer3D_MODEL);
	AddGameObject<M4A1>(Layer3D_MODEL);

	AddGameObject<CPlayer>(Layer3D_MODEL);
	AddGameObject<CEnemy>(Layer3D_MODEL);
	AddGameObject<CEnemy>(Layer3D_MODEL);
	AddGameObject<CEnemy>(Layer3D_MODEL);
	AddGameObject<CEnemyAI>(Layer3D_MODEL);
	AddGameObject<CSkybox>(Layer3D_SKYBOX);
	//AddGameObject<CM4A1>(Layer3D_MODEL);
	//AddGameObject<CFieldNormal>(Layer3D_MODEL);
	//AddGameObject<CSkydome>(Layer3D_MODEL);
	AddGameObject<CPolygon2D>(Layer2D_UI);

	bgm = new CAudioClip();
	bgm->Load("asset/sound/BGM/a.wav");
	bgm->Play(true);

	flag_result = false;

}

void CGame::Uninit()
{
	bgm->Stop();
	bgm->Unload();
	delete bgm;
	CScene::Uninit();
}

void CGame::Update()
{
	CScene::Update();

	if (flag_result)
	{
		CManager::SetScene<CResult>();
	}
	if (CInput::GetKeyTrigger(VK_RETURN))
	{
		CManager::SetScene<CResult>();
	}
}

void CGame::test()
{
	flag_result = true;
}
