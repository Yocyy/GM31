#pragma once
class CJudgement : public CGameObject
{
private:
	int Result_Cnt;
public:
	void Init();
	void Update();
	void Draw();
	void Uninit();
};
