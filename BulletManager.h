#pragma once
#include <vector>
#include <list>

class CStbTexture;

enum class BULLET_TYPE : unsigned int{
	MIN = -1,
	zero,
	one,
	MAX
};

class CBullet;

class CBulletManager : public CGameObject{
private:
	constexpr static unsigned int g_kBulletTexNum = 2;
	CScene* scene;
	CBullet* m_Bullet;
	std::list<CBullet*> list;
	std::vector<CStbTexture*> m_Texture;
public:
	void Init();
	void Uninit();
	void BulletDestroy();
	void AllBulletDestroy();
	void CreateBullet(XMFLOAT3 Position, XMFLOAT3 vec, BULLET_TYPE type);
};