#pragma once

#include "game_object.h"

class CDirectionalLight : public CGameObject{
private:
	LIGHT m_Light;
//	CShader m_Shader;
	ID3D11Buffer* m_LightBuffer;
public:
	void Init();
	void Update();
	void Draw();
};