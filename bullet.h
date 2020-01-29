#ifndef BULLET_H_
#define BULLET_H_

#include "collision.h"

constexpr float g_kBulletCircleSize(1);
class CModel;
class CBullet_Billboard;
class CStbTexture;
class CShader;

class CBullet : public CGameObject
{
private:
	constexpr static float m_kBulletSpeed{ 0.5f };
	std::list<CGameObject*> list;
	CShader* m_Shader;
	CModel* m_Model;
	CStbTexture* m_Texture;
	XMFLOAT3 m_front, m_right;
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