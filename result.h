#pragma once
class CScene;
class CStbTexture;
class CResult : public CScene
{
private:
	CStbTexture* m_Texture;
	CAudioClip* bgm;
public:
	void Init();
	void Uninit();
	void Update();
};