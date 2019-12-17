////=============================================================================
////
//// �X�J�C�h�[�������� [skydome.cpp]
////
////=============================================================================
//#include "main.h"
//#include "game_object.h"
//#include "renderer.h"
//#include "CreateShader.h"
//#include "skydome.h"
//#include "camera.h"
//#include "stb-texture.h"
//
////*****************************************************************************
//// �\���̐錾
////*****************************************************************************
//
//
////*****************************************************************************
//// �v���g�^�C�v�錾
////*****************************************************************************
//
//
////*****************************************************************************
//// �O���[�o���ϐ�
////*****************************************************************************
//
////-----------------------------------------------------------------------------
////-----------------------------------------------------------------------------
//
//
////=============================================================================
//// �X�J�C�h�[���̏�����
////=============================================================================
//void CSkydome::Init()
//{
//	//�O��
//	static XMFLOAT3 cross;
//
//	//���_�Aindex�f�[�^�̍ő�l�擾
//	g_Vertex_max = (surface_num + 1) * (surface_num + 1);
//	g_Index_max = (2 + surface_num * 2) * surface_num + (surface_num - 1) * 2;
//
//
//
//	//�o�b�t�@������ 
//	//g_pDevice = MyDirect3D_GetDevice();
//	//g_pDevice->CreateVertexBuffer(sizeof(MESH) * g_Vertex_max, D3DUSAGE_WRITEONLY, FVF_VERTEX3D, D3DPOOL_MANAGED, &g_VertexBuffer, NULL);
//	//g_pDevice->CreateIndexBuffer(sizeof(WORD) * g_Index_max, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_IndexBuffer, NULL);
//
//
//	//���_�o�b�t�@�̎擾 
//	MESH *pVertex;
//	g_VertexBuffer->Lock(0, 0, (void**)&pVertex, 0);
//	for (int z = 0; z <= surface_num; z++)
//	{
//		for (int x = 0; x <= surface_num; x++)
//		{
//			//���W
//			pVertex[z * (surface_num + 1) + x].Pos.x = cos(D3DXToRadian((360.0f / surface_num) * x)) * sin(D3DXToRadian((90.f / surface_num) * z)) * radius;
//			pVertex[z * (surface_num + 1) + x].Pos.z = -sin(D3DXToRadian((360.0f / surface_num) * x)) * sin(D3DXToRadian((90.f / surface_num) * z)) * radius;
//			pVertex[z * (surface_num + 1) + x].Pos.y = cos(D3DXToRadian((90.0f / surface_num) * z)) * radius;
//
//			//�O�ς���̖@��
//			D3DXVec3Cross(&cross, &pVertex[z * (surface_num + 1) + x].Pos, &pVertex[z * (surface_num + 1) + x].Pos);
//			pVertex[z * (surface_num + 1) + x].NVect = cross;
//
//			//uv�ݒ�
//			pVertex[z * (surface_num + 1) + x].uv = D3DXVECTOR2((1.0f / surface_num) * x, (1.0f / surface_num) * z);
//		}
//	}
//	g_VertexBuffer->Unlock();
//
//
//	//index�o�b�t�@�̎擾
//	WORD *pIndex;
//	g_IndexBuffer->Lock(0, 0, (void**)&pIndex, 0);
//
//	int i = 0;
//	for (int z = 0; z < surface_num; z++)
//	{
//		for (int x = 0; x <= surface_num; x++)
//		{
//			pIndex[i] = (z + 1) * (surface_num + 1) + x;
//			i++;
//			pIndex[i] = (z) * (surface_num + 1) + x;
//			i++;
//		}
//		if (z != surface_num - 1)
//		{
//			pIndex[i] = pIndex[i - 1];
//			i++;
//			pIndex[i] = (z + 2) * (surface_num + 1) + 0;
//			i++;
//		}
//	}
//	g_IndexBuffer->Unlock();
//
//
//	//�e�N�X�`���ݒ�
//	m_Texture->Load("");
//}
//
//
////=============================================================================
//// �X�J�C�h�[���̏I������
////=============================================================================
//void CSkydome::Uninit(void)
//{
//	m_VertexBuffer->Release();
//	m_IndexBuffer->Release();
//	m_Texture->Unload();
//	delete m_Texture;
//	m_Shader->Uninit();
//	delete m_Shader;
//}
//
//void Skydome_Update(void)
//{
//	spin++;
//}
//
////=============================================================================
//// �X�J�C�h�[���̕`��
////=============================================================================
//void CSkydome::Draw()
//{
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
//
//
//}