#ifndef ENEMY_H_
#define ENEMY_H_
#include "collision.h"
#include "modelAnimation.h"
#define ENEMY_RADIUS (1)

class CEnemy : public CGameObject
{
private:
	CModelAnimation* m_Model;
	bool flag_move;
	int ModelFrame = 0;
	int Animation = 0;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	XMFLOAT3 GetPosition();
	CIRCLE* circle;
};

#endif // !ENEMY_H_