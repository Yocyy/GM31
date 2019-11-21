#ifndef PLAYER_H_
#define PLAYER_H_

#define GRAVITE (9.8)
#define MASS (0.0005)
#define JUMP_FORCE (0.15)
class CAudioClip;
class CModel;
class CPlayer : public CGameObject
{
private:
	CModel* m_Model;
	CAudioClip* m_AudioClip;
	bool jump_flag;
	XMFLOAT3 velocity;	//‰Á‘¬“x
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
