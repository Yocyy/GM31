#ifndef BULLET_H_
#define BULLET_H_

#include "collision.h"

constexpr float g_kBulletCircleSize(1);
class CModel;
class CBillboard;
class CStbTexture;
class CBullet : public CGameObject
{
private:
	constexpr static float m_kBulletSpeed{ 0.5f };

	CModel* m_Model;
	CStbTexture* m_Texture;
	XMFLOAT3 g_front, g_right;
	float Bullet_Speed;
	const char* m_FileName;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	CIRCLE* circle;
	void SetBullet(CStbTexture* texture, XMFLOAT3 Position, XMFLOAT3 vec);
};

#endif // !BULLET_H_