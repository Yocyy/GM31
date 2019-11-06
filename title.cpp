#include "main.h"
#include "renderer.h"
#include "audio_clip.h"
#include "game_object.h"
#include "scene.h"
#include "input.h"
#include "polygon.h"
#include "title.h"
#include "manager.h"
#include "tuto.h"

void CTitle::Init()
{
	//AddGameObject<CCamera>(Layer3D_CAMERA);

	bgm = new CAudioClip();
	bgm->Load("asset/sound/BGM/a.wav");
	bgm->Play(true);
	m_Texture = new CTexture();
	m_Texture->Load("asset/title.tga");	// tgaフォーマットのαチャンネル付き圧縮しない。
	AddGameObject<CPolygon>(Layer2D_UI)->SetTexture(m_Texture);
}

void CTitle::Uninit()
{

	bgm->Stop();
	bgm->Unload();
	delete bgm;

	m_Texture->Unload();
	delete m_Texture;
	CScene::Uninit();
}

void CTitle::Update()
{
	CScene::Update();
	if (CInput::GetKeyTrigger(VK_RETURN))
	{
		CManager::SetScene<CTuto>();
	}
}


