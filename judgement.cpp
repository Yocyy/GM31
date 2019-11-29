#include "main.h"
#include "collision.h"
#include "texture.h"
#include "renderer.h"
#include "game_object.h"
#include "model.h"
#include "scene.h"
#include "manager.h"
#include "judgement.h"
#include "bullet.h"
#include "player.h"
#include "enemy.h"
#include "game.h"
#include "billboard.h"
#include "result.h"

void CJudgement::Init()
{
	Result_Cnt = 0;
}

void CJudgement::Update()
{
	////////////////////////////////////////////////////////////
////		“–‚½‚è”»’è
////////////////////////////////////////////////////////////
	std::vector<CEnemy*> enemys;
	enemys = CManager::GetScene()->GetGameObjects<CEnemy>(Layer3D_MODEL);
	std::vector<CBullet*> bullets;
	bullets = CManager::GetScene()->GetGameObjects<CBullet>(Layer3D_MODEL);
	for (CEnemy* enemy : enemys)
	{
		for (CBullet* bullet : bullets)
		{
			XMFLOAT3 enemyPos = enemy->GetPosition();
			
			if (Collision_IsHitCircle(enemy->circle, bullet->circle))
			{
				CScene* scene = CManager::GetScene();
				CBillboard* billborad = scene->AddGameObject<CBillboard>(Layer2D_UI);
				billborad->Bill_Create(enemyPos, "asset/title.tga");

				CManager::GetScene()->DestroyGameObject(enemy);
				CManager::GetScene()->DestroyGameObject(bullet);
				Result_Cnt++;
				return;
			}
		}
	}



	if (Result_Cnt >= 3)
	{
		CGame::test();
	}

}

void CJudgement::Draw()
{
}

void CJudgement::Uninit()
{
}
