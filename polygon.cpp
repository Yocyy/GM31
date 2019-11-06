#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "input.h"
#include "game_object.h"
#include "polygon.h"

static int a = 0;
// XM�Ƃ�
// DirectXMath���C�u����
void CPolygon::Init()
{
	VERTEX_3D vertex[4];
	vertex[0].Position = XMFLOAT3(0.0f, 0.0f, 0.0f);		// ���W
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);			// �@��
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);	// �F
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);				//uv

	vertex[1].Position = XMFLOAT3(SCREEN_WIDTH, 0.0f, 0.0f);		// ���W
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);			// �@��
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);	// �F
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);				//uv

	vertex[2].Position = XMFLOAT3(0.0f, SCREEN_HEIGHT, 0.0f);		// ���W
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);			// �@��
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);	// �F
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);				//uv

	vertex[3].Position = XMFLOAT3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);		// ���W
	vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);			// �@��
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);	// �F
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);				//uv

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;	// �\���̂̃T�C�Y
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// ���o�b�t�@�̐ݒ�
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;	// �ŏ��̒��_���i�[
	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
	//m_Texture = texture;
	//m_Texture->Load("asset/Test.tga");	// tga�t�H�[�}�b�g�̃��`�����l���t�����k���Ȃ��B
}



void CPolygon::Uninit()
{
	m_VertexBuffer->Release();
	//m_Texture->Unload();
	//delete m_Texture;
}

void CPolygon::Update()
{
	//if (CInput::GetKeyTrigger(VK_RETURN))
	//{
	//	a++;
	//	if (a == 3)
	//	{
	//		a = 0;
	//	}
	//}
	//if (a == 0)
	//{
	//	m_Texture->Load("asset/title.tga");
	//}
	//if (a == 1)
	//{
	//	m_Texture->Load("asset/tuto.tga");
	//}

}

void CPolygon::Draw()
{
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);	//	���_�o�b�t�@��ݒ� 9����SetVertexBuffer
	CRenderer::SetTexture(m_Texture);	// �e�N�X�`���ݒ�
	CRenderer::SetWorldViewProjection2D();	// 2D�}�g���N�X�ݒ�
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);	//	�g�|���W�ݒ�	���g�|���W = �ǂ�����Đ������Ԃ��B���̏ꍇ��TRIANGLESTRIP�^�Ō���
	CRenderer::GetDeviceContext()->Draw(4, 0);	//	�|���S���`��
}

void CPolygon::SetTexture(CTexture* texture)
{
	m_Texture = texture;
}
