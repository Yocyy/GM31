#include "main.h"
#include "renderer.h"
#include "audio_clip.h"
#include "game_object.h"
#include "scene.h"
#include "input.h"
#include "result.h"
#include "title.h"
#include "manager.h"
#include "camera.h"
#include "polygon.h"

void CResult::Init()
{
	//AddGameObject<CCamera>(Layer3D_CAMERA);
	//AddGameObject<CPolygon>(Layer2D_UI);
	ShowCursor(true);
	bgm = new CAudioClip();
	bgm->Load("asset/sound/BGM/a.wav");
	bgm->Play(true);
}

void CResult::Uninit()
{

	bgm->Stop();
	bgm->Unload();
	delete bgm;
	CScene::Uninit();
}

void CResult::Update()
{
	CScene::Update();
	if (CInput::GetKeyTrigger(VK_RETURN))
	{
		CManager::SetScene<CTitle>();
	}
}