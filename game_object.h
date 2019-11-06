#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

class CGameObject
{
private:
	bool m_Destroy = false;
protected:
	XMFLOAT3 m_Position;
	XMFLOAT3 m_Rotation;
	XMFLOAT3 m_Scale;

public:
	CGameObject() {}
	virtual ~CGameObject() {}
	virtual void Init(){}
	virtual void Uninit() {}
	virtual void Update() {}
	virtual void Draw() {}
	virtual void SetDestroy()
	{
		m_Destroy = true;
	}
	virtual bool Destroy()
	{
		if (m_Destroy)
		{
			Uninit();
			delete this;
			return true;
		}
		else
		{
			return false;
		}
	}
};

#endif // !GAMEOBJECT_H_