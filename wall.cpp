#include "main.h"
#include "stb-texture.h"
#include "renderer.h"
#include "game_object.h"
#include "wall.h"
#include "camera.h"
#include "manager.h"
#include "scene.h"
#include "Shader.h"

#define VERTEX_BUEEFER (8)

// XM�Ƃ�
// DirectXMath���C�u����
void CWall::Init()
{
	VERTEX_3D vertex[VERTEX_BUEEFER];

	//����
	vertex[0].Position = XMFLOAT3(-100.0f, 0.0f, 0.0f);		// ���W
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);			// �@��
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);	// �F
	vertex[0].TexCoord = XMFLOAT2(0.0f, 1.0f);				//uv

	vertex[1].Position = XMFLOAT3(-100.0f, 50.0f, 0.0f);		// ���W
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);			// �@��
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);	// �F
	vertex[1].TexCoord = XMFLOAT2(0.0f, 0.0f);				//uv
	//���ʕ�
	vertex[2].Position = XMFLOAT3(-100.0f, 0.0f, 200.0f);		// ���W
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);			// �@��
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);	// �F
	vertex[2].TexCoord = XMFLOAT2(1.0f, 1.0f);				//uv

	vertex[3].Position = XMFLOAT3(-100.0f, 50.0f, 200.0f);		// ���W
	vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);			// �@��
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);	// �F
	vertex[3].TexCoord = XMFLOAT2(1.0f, 0.0f);				//uv

	vertex[4].Position = XMFLOAT3(100.0f, 0.0f, 200.0f);		// ���W
	vertex[4].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);			// �@��
	vertex[4].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);	// �F
	vertex[4].TexCoord = XMFLOAT2(2.0f, 1.0f);				//uv

	vertex[5].Position = XMFLOAT3(100.0f, 50.0f, 200.0f);		// ���W
	vertex[5].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);			// �@��
	vertex[5].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);	// �F
	vertex[5].TexCoord = XMFLOAT2(2.0f, 0);				//uv
	//�E�ʕ�
	vertex[6].Position = XMFLOAT3(100.0f, 0.0f, 0.0f);		// ���W
	vertex[6].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);			// �@��
	vertex[6].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);	// �F
	vertex[6].TexCoord = XMFLOAT2(3.0f, 1.0f);				//uv

	vertex[7].Position = XMFLOAT3(100.0f, 50.0f, 0.0f);		// ���W
	vertex[7].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);			// �@��
	vertex[7].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);	// �F
	vertex[7].TexCoord = XMFLOAT2(15.0f, 0.0f);				//uv

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * VERTEX_BUEEFER;	// �\���̂̃T�C�Y
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// ���o�b�t�@�̐ݒ�
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;	// �ŏ��̒��_���i�[
	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
	m_Texture = new CStbTexture();
	m_Texture->Load("asset/TEXTURE/tree_001.jpg");	// tga�t�H�[�}�b�g�̃��`�����l���t�����k���Ȃ��B

	m_Shader = new CShader();
	m_Shader->Init(VS_CSO::Shader_3D, PS_CSO::Shader_3D);
}

void CWall::Uninit()
{
	m_VertexBuffer->Release();
	m_Texture->Unload();
	delete m_Texture;

	m_Shader->Uninit();
	delete m_Shader;
}

void CWall::Update()
{
}


void CWall::Draw()
{
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);	//	���_�o�b�t�@��ݒ� 9����SetVertexBuffer
	CRenderer::SetTexture(m_Texture);	// �e�N�X�`���ݒ�
	XMMATRIX world;
	world = XMMatrixScaling(0.1f, 0.1f, 0.1f);		//�g��k��
	world *= XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);		//��]
	world *= XMMatrixTranslation(0.0f, 0.0f, 0.0f);		//�ړ�
	
	XMFLOAT4X4 world4x4;
	XMStoreFloat4x4(&world4x4, world);
	m_Shader->SetWorldMatrix(&world4x4);
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	XMFLOAT4X4 viewmatrix4x4;
	CCamera* camera = CManager::GetScene()->GetGameObject<CCamera>(Layer3D_CAMERA);
	XMStoreFloat4x4(&viewmatrix4x4, camera->Get_Camera_ViewMatrix());
	m_Shader->SetViewMatrix(&viewmatrix4x4);

	XMFLOAT4X4 promatrix4x4;
	XMStoreFloat4x4(&promatrix4x4, camera->Get_Camera_Projection());
	m_Shader->SetProjectionMatrix(&promatrix4x4);

	m_Shader->SetCameraPosition(&camera->Get_Camera_Position4f());

	m_Shader->Set();

	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);	//	�g�|���W�ݒ�	���g�|���W = �ǂ�����Đ������Ԃ��B���̏ꍇ��TRIANGLESTRIP�^�Ō���
	CRenderer::GetDeviceContext()->Draw(VERTEX_BUEEFER, 0);	//	�|���S���`��

}