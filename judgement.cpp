#include "main.h"
#include "collision.h"
#include "stb-texture.h"
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
#include "enemyAI.h"
#include "player.h"

void CJudgement::Init()
{
	Result_Cnt = 0;
}

void CJudgement::Update()
{
////////////////////////////////////////////////////////////
////		�����蔻��
////////////////////////////////////////////////////////////

	//�P�̂̃I�u�W�F�N�g
	CPlayer* player;
	player = CManager::GetScene()->GetGameObject<CPlayer>(Layer3D_MODEL);

	//�����̃I�u�W�F�N�g
	std::vector<CEnemy*> enemys;
	enemys = CManager::GetScene()->GetGameObjects<CEnemy>(Layer3D_MODEL);
	std::vector<CEnemyAI*> enemyAIs;
	enemyAIs = CManager::GetScene()->GetGameObjects<CEnemyAI>(Layer3D_MODEL);
	std::vector<CBullet*> bullets;
	bullets = CManager::GetScene()->GetGameObjects<CBullet>(Layer3D_EFFECT);

	//bullet �� enemy
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
			}
		}
	}

	//player �� enemyAI
	for (CEnemyAI* enemyAI : enemyAIs)
	{
		XMFLOAT3 enemyAIPos = enemyAI->GetPosition();
		enemyAI->moveflag = false;

		if (Collision_IsHitCircle(enemyAI->circle, player->circle))
		{
			enemyAI->moveflag = true;
		}
	}


	if (Result_Cnt >= 3)
	{
		CGame::test();
	}

	return;
}

void CJudgement::Draw()
{
}

void CJudgement::Uninit()
{
}
