#include "main.h"
#include "renderer.h"
#include "Shader.h"
#include <io.h>




void CShader::Init(const VS_CSO VSIndex, const PS_CSO PSIndex) {

	assert(VSIndex != VS_CSO::MIN || VSIndex != VS_CSO::MAX);//error check
	assert(PSIndex != PS_CSO::MIN || PSIndex != PS_CSO::MAX);//error check
	// 頂点シェーダ生成
	{
		FILE* file;
		long int fsize;

		file = fopen(VSshaderfile[static_cast<unsigned int>(VSIndex)], "rb");
		fsize = _filelength(_fileno(file));
		unsigned char* buffer = new unsigned char[fsize];
		fread(buffer, fsize, 1, file);
		fclose(file);

		CRenderer::GetDevice()->CreateVertexShader(buffer, fsize, NULL, &m_VertexShader);


		// 入力レイアウト生成
		{
			D3D11_INPUT_ELEMENT_DESC layout[] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};
			UINT numElements = ARRAYSIZE(layout);

			CRenderer::GetDevice()->CreateInputLayout(layout,
				numElements,
				buffer,
				fsize,
				&m_VertexLayout);
		}

		delete[] buffer;
	}



	// ピクセルシェーダ生成
	{
		FILE* file;
		long int fsize;

		file = fopen(PSshaderfile[static_cast<unsigned int>(PSIndex)], "rb");
		fsize = _filelength(_fileno(file));
		unsigned char* buffer = new unsigned char[fsize];
		fread(buffer, fsize, 1, file);
		fclose(file);

		CRenderer::GetDevice()->CreatePixelShader(buffer, fsize, NULL, &m_PixelShader);

		delete[] buffer;
	}



	// 定数バッファ生成
	{
		D3D11_BUFFER_DESC hBufferDesc;
		hBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		hBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		hBufferDesc.CPUAccessFlags = 0;
		hBufferDesc.MiscFlags = 0;
		hBufferDesc.StructureByteStride = sizeof(float);

		hBufferDesc.ByteWidth = sizeof(CONSTANT);
		CRenderer::GetDevice()->CreateBuffer(&hBufferDesc, NULL, &m_ConstantBuffer);
	}

	// 定数バッファ生成
	{
		D3D11_BUFFER_DESC hBufferDesc;
		hBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		hBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		hBufferDesc.CPUAccessFlags = 0;
		hBufferDesc.MiscFlags = 0;
		hBufferDesc.StructureByteStride = sizeof(float);

		hBufferDesc.ByteWidth = sizeof(MATERIAL);
		CRenderer::GetDevice()->CreateBuffer(&hBufferDesc, NULL, &m_MaterialBuffer);
	}

	m_Material.Ambient = COLOR(0, 0, 0, 0);
	m_Material.Diffuse = COLOR(1, 1, 1, 0);
	m_Material.Emission = COLOR(1, 1, 1, 1);
	m_Material.SpecularColor = COLOR(1, 1, 1, 1);
	m_Material.Shininess = 20;
}




void CShader::Uninit()
{
	if (m_VertexLayout)		m_VertexLayout->Release();
	if (m_VertexShader)		m_VertexShader->Release();
	if (m_PixelShader)		m_PixelShader->Release();

	if (m_ConstantBuffer)	m_ConstantBuffer->Release();
	if (m_MaterialBuffer)	m_MaterialBuffer->Release();
	if (m_LightBuffer)	m_LightBuffer->Release();
	if (m_VertexBuffer)	m_VertexBuffer->Release();
	if (m_IndexBuffer)	m_IndexBuffer->Release();
}




void CShader::Set()
{

	// シェーダ設定
	CRenderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	CRenderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);


	// 入力レイアウト設定
	CRenderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);


	// 定数バッファ更新
	CRenderer::GetDeviceContext()->UpdateSubresource(m_ConstantBuffer, 0, NULL, &m_Constant, 0, 0);	//コンスタント
	CRenderer::GetDeviceContext()->UpdateSubresource(m_MaterialBuffer, 0, NULL, &m_Material, 0, 0);	//マテリアル

	// 定数バッファ設定
	CRenderer::GetDeviceContext()->VSSetConstantBuffers(0, 1, &m_ConstantBuffer);

	CRenderer::GetDeviceContext()->PSSetConstantBuffers(0, 1, &m_ConstantBuffer);
	CRenderer::GetDeviceContext()->PSSetConstantBuffers(1, 1, &m_MaterialBuffer);
}