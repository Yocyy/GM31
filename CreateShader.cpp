#include "main.h"
#include "render.h"
#include "CreateShader.h"
#include <io.h>





void CCreateShader::Init(const char* VertexShader, const char* PixelShader)
{

	// 頂点シェーダ生成
	{
		FILE* file;
		long int fsize;

		file = fopen(VertexShader, "rb");
		fsize = _filelength(_fileno(file));
		unsigned char* buffer = new unsigned char[fsize];
		fread(buffer, fsize, 1, file);
		fclose(file);

		CRender::GetDevice()->CreateVertexShader(buffer, fsize, NULL, &m_VertexShader);


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

			CRender::GetDevice()->CreateInputLayout(layout,
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

		file = fopen(PixelShader, "rb");
		fsize = _filelength(_fileno(file));
		unsigned char* buffer = new unsigned char[fsize];
		fread(buffer, fsize, 1, file);
		fclose(file);

		CRender::GetDevice()->CreatePixelShader(buffer, fsize, NULL, &m_PixelShader);

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
		CRender::GetDevice()->CreateBuffer(&hBufferDesc, NULL, &m_ConstantBuffer);
	}

	// 定数バッファ生成
	{
		D3D11_BUFFER_DESC hBufferDesc;
		hBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		hBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		hBufferDesc.CPUAccessFlags = 0;
		hBufferDesc.MiscFlags = 0;
		hBufferDesc.StructureByteStride = sizeof(float);

		hBufferDesc.ByteWidth = sizeof(LIGHT);
		CRender::GetDevice()->CreateBuffer(&hBufferDesc, NULL, &m_LightBuffer);
	}
	m_Light.Direction = XMFLOAT4(0.0f, -1.0f, 0.0f, 0.0f);	//ライトベクトル
	m_Light.Diffuse = COLOR(0.0f, 0.0f, 0.0f, 0.0f);	//ライトカラー
	m_Light.Ambient = COLOR(0.0f, 0.0f, 0.0f, 0.0f);	//環境光
}




void CCreateShader::Uninit()
{
	if (m_ConstantBuffer)	m_ConstantBuffer->Release();

	if (m_VertexLayout)		m_VertexLayout->Release();
	if (m_VertexShader)		m_VertexShader->Release();
	if (m_PixelShader)		m_PixelShader->Release();
}




void CCreateShader::Set()
{

	// シェーダ設定
	CRender::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	CRender::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);


	// 入力レイアウト設定
	CRender::GetDeviceContext()->IASetInputLayout(m_VertexLayout);


	// 定数バッファ更新
	CRender::GetDeviceContext()->UpdateSubresource(m_ConstantBuffer, 0, NULL, &m_Constant, 0, 0);	//コンスタント
	CRender::GetDeviceContext()->UpdateSubresource(m_LightBuffer, 0, NULL, &m_Light, 0, 0);			//ライト
	CRender::GetDeviceContext()->UpdateSubresource(m_MaterialBuffer, 0, NULL, &m_Material, 0, 0);	//マテリアル

	// 定数バッファ設定
	CRender::GetDeviceContext()->VSSetConstantBuffers(0, 1, &m_ConstantBuffer);
	CRender::GetDeviceContext()->VSSetConstantBuffers(1, 1, &m_LightBuffer);

	CRender::GetDeviceContext()->PSSetConstantBuffers(0, 1, &m_ConstantBuffer);
	CRender::GetDeviceContext()->PSSetConstantBuffers(1, 1, &m_LightBuffer);
}