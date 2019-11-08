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

void CGame::Init()
{
	ShowCursor(false);

	AddGameObject<CCamera>(Layer3D_CAMERA);
	AddGameObject<CField>(Layer3D_MODEL);
	AddGameObject<CWall>(Layer3D_MODEL);
	AddGameObject<CPlayer>(Layer3D_MODEL);
	AddGameObject<CEnemy>(Layer3D_MODEL);
	AddGameObject<CEnemy>(Layer3D_MODEL);
	AddGameObject<CEnemy>(Layer3D_MODEL);
	AddGameObject<CBall>(Layer3D_MODEL);

	bgm = new CAudioClip();
	bgm->Load("asset/sound/BGM/a.wav");
	bgm->Play(true);

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

	if (CInput::GetKeyTrigger(VK_RETURN))
	{
		CManager::SetScene<CResult>();
	}
}
