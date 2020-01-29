//=============================================================================
//
// �X�J�C�h�[�������� [skydome.cpp]
//
//=============================================================================
#include "main.h"
#include "stb-texture.h"
#include "game_object.h"
#include "renderer.h"
#include "Shader.h"
#include "skydome.h"
#include "camera.h"
#include "scene.h"
#include "manager.h"

//=============================================================================
// �X�J�C�h�[���̏�����
//=============================================================================
void CSkydome::Init()
{
	//�e�N�X�`���ݒ�
	m_Texture = new CStbTexture();
	m_Texture->Load("asset/field004.tga");

	//�O��
	XMVECTOR cross;

	//���_�Aindex�f�[�^�̍ő�l�擾
	g_Vertex_max = (surface_num + 1) * (surface_num + 1);
	g_Index_max = (2 + surface_num * 2) * surface_num + (surface_num - 1) * 2;



	//�o�b�t�@������ 
	//g_pDevice = MyDirect3D_GetDevice();
	//g_pDevice->CreateVertexBuffer(sizeof(MESH) * g_Vertex_max, D3DUSAGE_WRITEONLY, FVF_VERTEX3D, D3DPOOL_MANAGED, &g_VertexBuffer, NULL);
	//g_pDevice->CreateIndexBuffer(sizeof(WORD) * g_Index_max, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_IndexBuffer, NULL);
	//CScene* scene = CManager::GetScene();
	//CRenderer::GetDevice()->CreateBuffer()
	//m_VertexBuffer



	//���_�o�b�t�@�̎擾 
	SKYMESH *pVertex;
	pVertex = new SKYMESH();
	for (int z = 0; z <= surface_num; z++)
	{
		for (int x = 0; x <= surface_num; x++)
		{
			//���W
			pVertex[z * (surface_num + 1) + x].Pos.x = cos(XMConvertToRadians((360.0f / surface_num) * x)) * sin(XMConvertToRadians((90.f / surface_num) * z)) * radius;
			pVertex[z * (surface_num + 1) + x].Pos.z = -sin(XMConvertToRadians((360.0f / surface_num) * x)) * sin(XMConvertToRadians((90.f / surface_num) * z)) * radius;
			pVertex[z * (surface_num + 1) + x].Pos.y = cos(XMConvertToRadians((90.0f / surface_num) * z)) * radius;

			//�O�ς���̖@��
			cross = XMVector3Cross(XMLoadFloat3(&pVertex[z * (surface_num + 1) + x].Pos), XMLoadFloat3(&pVertex[z * (surface_num + 1) + x].Pos));
			XMStoreFloat3(&pVertex[z * (surface_num + 1) + x].NVect,cross);

			//uv�ݒ�
			pVertex[z * (surface_num + 1) + x].uv = XMFLOAT2((1.0f / surface_num) * x, (1.0f / surface_num) * z);
		}
	}
	//g_VertexBuffer->Unlock();

	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = g_Vertex_max;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = pVertex;

		CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
	}


	//index�o�b�t�@�̎擾
	WORD *pIndex;
	pIndex = new WORD();
	//g_IndexBuffer->Lock(0, 0, (void**)&pIndex, 0);

	int i = 0;
	for (int z = 0; z < surface_num; z++)
	{
		for (int x = 0; x <= surface_num; x++)
		{
			pIndex[i] = (z + 1) * (surface_num + 1) + x;
			i++;
			pIndex[i] = (z) * (surface_num + 1) + x;
			i++;
		}
		if (z != surface_num - 1)
		{
			pIndex[i] = pIndex[i - 1];
			i++;
			pIndex[i] = (z + 2) * (surface_num + 1) + 0;
			i++;
		}
	}
	//g_IndexBuffer->Unlock();

	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = g_Index_max;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = pIndex;

		CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
	}


}


//=============================================================================
// �X�J�C�h�[���̏I������
//=============================================================================
void CSkydome::Uninit(void)
{
	m_VertexBuffer->Release();
	m_IndexBuffer->Release();
	m_Texture->Unload();
	delete m_Texture;
	m_Shader->Uninit();
	delete m_Shader;
}

void CSkydome::Update(void)
{
	spin++;
}

//=============================================================================
// �X�J�C�h�[���̕`��
//=============================================================================
void CSkydome::Draw()
{
//	//--------------------------------------------------
//	//          �s��錾�A�P�ʍs��
//	//--------------------------------------------------
//
//
//	//--------------------------------------------------
//	//          �s��̈ړ��A��]�A�k�����A����
//	//--------------------------------------------------
//
//
//	//--------------------------------------------------
//	//          �f�o�C�X�Z�b�e�B���O
//	//--------------------------------------------------
//	//�f�o�C�X�֍s���ݒ�
//	g_pDevice->SetTransform(D3DTS_WORLD, &mtxMatrix);
//
//
//	//���_�f�[�^�`��̐ݒ�
//	g_pDevice->SetStreamSource(0, g_VertexBuffer, 0, sizeof(MESH));
//	g_pDevice->SetIndices(g_IndexBuffer);
//
//
//	//���C�e�B���O
//	g_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
//
//	//FVF�̐ݒ�
//	g_pDevice->SetFVF(FVF_VERTEX3D);
//
//	//�e�N�X�`���̐ݒ�
//	g_pDevice->SetTexture(0, g_pTexture);
//
//
//	//--------------------------------------------------
//	//          �`��J�n
//	//--------------------------------------------------
//	g_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_Vertex_max, 0, g_Index_max - 2);
//
//
//	//--------------------------------------------------
//	//          �f�o�C�X�ăZ�b�e�B���O
//	//--------------------------------------------------



	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// �C���f�b�N�X�o�b�t�@�ݒ�
	CRenderer::GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R16_UINT, 0);


	// �e�N�X�`���ݒ�
	CRenderer::SetTexture(m_Texture);

	// �}�g���N�X�ݒ�
	XMMATRIX world;
	world = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

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

	// �v���~�e�B�u�g�|���W�ݒ�
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);


	// �|���S���`��
	//CRenderer::GetDeviceContext()->DrawIndexed(((FIELD_X * 2 + 2) * (FIELD_Z - 1) - 2), 0, 0);
}