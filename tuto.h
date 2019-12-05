#ifndef TUTO_H_
#define TUTO_H_
class CScene;
class CTuto : public CScene
{
private:
	CAudioClip* bgm;
	CStbTexture* m_Texture = NULL;
public:
	void Init();
	void Uninit();
	void Update();
};

#endif // !TUTO_H_