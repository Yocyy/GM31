#include "main.h"
#include "render.h"
#include "CreateShader.h"
#include <io.h>





void CCreateShader::Init(const char* VertexShader, const char* PixelShader)
{

	// ���_�V�F�[�_����
	{
		FILE* file;
		long int fsize;

		file = fopen(VertexShader, "rb");
		fsize = _filelength(_fileno(file));
		unsigned char* buffer = new unsigned char[fsize];
		fread(buffer, fsize, 1, file);
		fclose(file);

		CRender::GetDevice()->CreateVertexShader(buffer, fsize, NULL, &m_VertexShader);


		// ���̓��C�A�E�g����
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



	// �s�N�Z���V�F�[�_����
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



	// �萔�o�b�t�@����
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

	// �萔�o�b�t�@����
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
	m_Light.Direction = XMFLOAT4(0.0f, -1.0f, 0.0f, 0.0f);	//���C�g�x�N�g��
	m_Light.Diffuse = COLOR(0.0f, 0.0f, 0.0f, 0.0f);	//���C�g�J���[
	m_Light.Ambient = COLOR(0.0f, 0.0f, 0.0f, 0.0f);	//����
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

	// �V�F�[�_�ݒ�
	CRender::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	CRender::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);


	// ���̓��C�A�E�g�ݒ�
	CRender::GetDeviceContext()->IASetInputLayout(m_VertexLayout);


	// �萔�o�b�t�@�X�V
	CRender::GetDeviceContext()->UpdateSubresource(m_ConstantBuffer, 0, NULL, &m_Constant, 0, 0);	//�R���X�^���g
	CRender::GetDeviceContext()->UpdateSubresource(m_LightBuffer, 0, NULL, &m_Light, 0, 0);			//���C�g
	CRender::GetDeviceContext()->UpdateSubresource(m_MaterialBuffer, 0, NULL, &m_Material, 0, 0);	//�}�e���A��

	// �萔�o�b�t�@�ݒ�
	CRender::GetDeviceContext()->VSSetConstantBuffers(0, 1, &m_ConstantBuffer);
	CRender::GetDeviceContext()->VSSetConstantBuffers(1, 1, &m_LightBuffer);

	CRender::GetDeviceContext()->PSSetConstantBuffers(0, 1, &m_ConstantBuffer);
	CRender::GetDeviceContext()->PSSetConstantBuffers(1, 1, &m_LightBuffer);
}