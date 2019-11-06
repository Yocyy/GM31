#pragma once

class CScene;
class CGame : public CScene
{
private:
	CAudioClip* bgm;

public:
	void Init();
	void Uninit();
	void Update();
};			 