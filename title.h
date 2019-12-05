#ifndef TITLE_H_
#define TITLE_H_
class CScene;
class CTitle : public CScene
{
private:
	CAudioClip* bgm;
	CStbTexture* m_Texture = NULL;
public:
	void Init();
	void Uninit();
	void Update();
};

#endif // !TITLE_H_