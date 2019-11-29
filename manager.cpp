#include "main.h"
#include "audio_clip.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "game_object.h"	//Ç±Ç±Ç©ÇÁ
#include "model.h"
#include "polygon.h"
#include "wall.h"
#include "mesh_field.h"
#include "scene.h"			//Ç±Ç±Ç‹Ç≈ÇÕCGame_ObjectÇÃåpè≥êÊ
#include "title.h"
#include "camera.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "result.h"


CScene* CManager::scene = nullptr;
void CManager::Init()
{
	CRenderer::Init();
	CAudioClip::Init();
	CInput::Init();

	SetScene<CTitle>();
}

void CManager::Uninit()
{
	scene->Uninit();
	delete scene;

	CAudioClip::Uninit();
	CInput::Uninit();
	CRenderer::Uninit();
}

void CManager::Update()
{
	CInput::Update();

	scene->Update();
}

void CManager::Draw()
{

	CRenderer::Begin();

	scene->Draw();

	CRenderer::End();

}

CScene * CManager::GetScene()
{
	return scene;
}