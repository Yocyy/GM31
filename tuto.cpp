#include "main.h"
#include "renderer.h"
#include "audio_clip.h"
#include "game_object.h"
#include "scene.h"
#include "input.h"
#include "polygon.h"
#include "tuto.h"
#include "manager.h"
#include "game.h"
#include "stb-texture.h"

void CTuto::Init()
{
	bgm = new CAudioClip();
	bgm->Load("asset/sound/BGM/a.wav");
	bgm->Play(true);
	m_Texture = new CStbTexture();
	m_Texture->Load("asset/tuto.tga");	// tgaフォーマットのαチャンネル付き圧縮しない。
	AddGameObject<CPolygon>(Layer2D_UI)->SetTexture(m_Texture);
}

void CTuto::Uninit()
{
	bgm->Stop();
	bgm->Unload();
	delete bgm;

	m_Texture->Unload();
	delete m_Texture;
	CScene::Uninit();
}

void CTuto::Update()
{
	CScene::Update();
	if (CInput::GetKeyTrigger(VK_RETURN))
	{
		CManager::SetScene<CGame>();
	}
}