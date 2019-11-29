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
	XMFLOAT4X4  m_ViewMatrix;
	XMFLOAT4X4  m_InvViewMatrix;
	XMFLOAT4X4  m_ProjectionMatrix;
;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void Set_Player(CPlayer* player);
	XMMATRIX Get_Camera_ViewMatrix();
	XMMATRIX Get_Camera_InvViewMatrix();
	XMMATRIX Get_Camera_Projection();
	bool GetVisibility(XMFLOAT3 Position , float Radius);
};

#endif // !CAMERA_H_