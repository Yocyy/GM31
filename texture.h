#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "main.h"
#include "renderer.h"

class CTexture
{

public:

	void Load(const char *FileName);
	void Unload();

	ID3D11ShaderResourceView* GetShaderResourceView() { return m_ShaderResourceView; }


private:

	ID3D11Texture2D*			m_Texture;
	ID3D11ShaderResourceView*	m_ShaderResourceView;

};

#endif // !TEXTURE_H_