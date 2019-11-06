#ifndef CAMERA_H_
#define CAMERA_H_

class CPlayer;

class CCamera : public CGameObject
{
private:

	//XMMATRIX m_ViewMatrix;
	RECT m_Viewport;
	CPlayer* m_Player;
	POINT oldpt;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void Set_Player(CPlayer* player);
};

#endif // !CAMERA_H_