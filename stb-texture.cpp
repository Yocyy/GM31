#include "stb-texture.h"
#include <vector>

void CStbTexture::Load(const char *FileName)
{
	unsigned char* pixels = NULL;
	int bpp = NULL;
	int width = NULL;
	int height = NULL;

	pixels = stbi_load(FileName, &width, &height, &bpp, 4);




	D3D11_TEXTURE2D_DESC desc;
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = pixels;
	initData.SysMemPitch = width * 4;
	initData.SysMemSlicePitch = initData.SysMemPitch * height;

	auto hr = CRenderer::GetDevice()->CreateTexture2D(&desc, &initData, &m_Texture);
	if (FAILED(hr)) {
		assert(false);
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc = {};
	SRVDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	//SRVDesc.Texture2D.MostDetailedMip = 10;
	SRVDesc.Texture2D.MipLevels = 1;

	hr = CRenderer::GetDevice()->CreateShaderResourceView(m_Texture, &SRVDesc, &m_ShaderResourceView);
	if (FAILED(hr))
	{
		assert(false);
	}

	// ƒƒ‚ƒŠã‚Ì‰æ‘œƒf[ƒ^‚ð”jŠü
	stbi_image_free(pixels);
}


void CStbTexture::Unload()
{
	m_Texture->Release();
	m_ShaderResourceView->Release();
}



