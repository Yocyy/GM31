#ifndef BULLET_H_
#define BULLET_H_
#include "collision.h"
#define BULLET_RADIUS (1)
class CBullet : public CGameObject
{
private:
	CModel* m_Model;
	XMFLOAT3 g_front, g_right;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void SetPosition(XMFLOAT3 position, XMFLOAT3 front);
	CIRCLE* circle;
};

#endif // !BULLET_H_
