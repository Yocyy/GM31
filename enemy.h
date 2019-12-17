#pragma
#include "collision.h"
#include "modelAnimation.h"

class CShader;
class CEnemy : public CGameObject
{
private:
	constexpr static float m_kCircleSize{1.0f};

	CShader* m_Shader;
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