#ifndef JUDGEMENT_H_
#define JUDGEMENT_H_

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

#endif // !JUDGEMENT_H_

