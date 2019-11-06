#ifndef PLAYER_H_
#define PLAYER_H_
class CAudioClip;
class CModel;
class CPlayer : public CGameObject
{
private:
	CModel* m_Model;
	CAudioClip* m_AudioClip;
public:
	XMFLOAT3 g_front = XMFLOAT3(0.0f, 0.0f, 1.0f);
	XMFLOAT3 g_right = XMFLOAT3(1.0f, 0.0f, 0.0f);
	XMFLOAT3 g_up = XMFLOAT3(0.0f, 1.0f, 0.0f);
	void Init();
	void Uninit();
	void Update();
	void Draw();
	XMFLOAT3 Get_Player_Position();
	XMFLOAT3 Get_Player_Rotation();
	XMFLOAT3 Get_Player_Front();
};

#endif // !PLAYER_H_
