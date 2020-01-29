#pragma once
class CAudioClip;
class CShader;
class CModelAnimation;

class Weapons
{
protected:
	CAudioClip* m_AudioClip;
	CShader*	m_Shader;
	CModelAnimation* m_Model;
	bool m_CurrentWeapon = false;
public:
	virtual void Action() = 0;	// 左クリック
	virtual void Peak() = 0;	// 右クリック
	virtual void Reload() = 0;	// Rキー
	void Enable() { m_CurrentWeapon = true; };
	void IsEnable() { m_CurrentWeapon = false; };
};

class KNIFE : public Weapons, public CGameObject
{
public:
	void Action() override;
	void Peak() override;
	void Reload() override;

	void Init() override;
	void Update() override;
	void Draw() override;
	void Uninit() override;
};

class AK : public Weapons, public CGameObject
{
private:
	constexpr static unsigned int m_kBulletMaxNum = { 20 };
	int m_BulletNum;
	float m_Rait = 20;
public:
	void Action() override;
	void Peak() override;
	void Reload() override;

	void Init() override;
	void Update() override;
	void Draw() override;
	void Uninit() override;
};

class M4A1 : public Weapons, public CGameObject
{
private:
	constexpr static unsigned int m_kBulletMaxNum = { 30 };
	int m_BulletNum;
public:
	void Action() override;
	void Peak() override;
	void Reload() override;

	void Init() override;
	void Update() override;
	void Draw() override;
	void Uninit() override;
};