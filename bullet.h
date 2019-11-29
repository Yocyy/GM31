#ifndef BULLET_H_
#define BULLET_H_

#include "collision.h"

#define BULLET_RADIUS (1)
#define BULLET_SPEED (0.5)
class CModel;
class CTexture;
class CBillboard;
class CBullet : public CGameObject
{
private:
	CModel* m_Model;
	//CTexture* m_Texture;
	//CBillboard* m_Billboard;
	XMFLOAT3 g_front, g_right;
	float Bullet_Speed;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	CIRCLE* circle;
};

#endif // !BULLET_H_