#ifndef CAMERA_H_
#define CAMERA_H_

class CPlayer;
class CShader;
class CCamera : public CGameObject
{
private:
	CShader* m_Shader;
	//XMMATRIX m_ViewMatrix;
	RECT m_Viewport;
	CPlayer* m_Player;
	POINT oldpt;
	XMFLOAT4X4  m_ViewMatrix;
	XMFLOAT4X4  m_InvViewMatrix;
	XMFLOAT4X4  m_ProjectionMatrix;
	POINT pt;
	bool Debug_flag = false;
	bool m_ScopeEnable;
	float Center_X, Center_Y;
	float fov,aspect,nearZ,farZ;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void Set_Player(CPlayer* player);
	XMMATRIX Get_Camera_ViewMatrix();
	XMMATRIX Get_Camera_InvViewMatrix();
	XMMATRIX Get_Camera_Projection();
	XMFLOAT3 Get_Camera_Position();
	XMFLOAT4 Get_Camera_Position4f();
	XMFLOAT3 Get_Camera_Rotation();
	bool GetVisibility(XMFLOAT3 Position , float Radius);
	void ScopeEnable(void);
	void ScopeIsEnable(void);
};

#endif // !CAMERA_H_