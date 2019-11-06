#include "main.h"
#include "texture.h"
#include "renderer.h"
#include "game_object.h"
#include "mesh_field.h"

static int g_Vertex_max;
static int g_Index_max;

// XM�Ƃ�
// DirectXMath���C�u����
void CMesh_Field::Init()
{

	vertex = XMINT3(5, 0, 5);
	
	g_Vertex_max = (vertex.x + 1) * (vertex.z + 1);
	g_Index_max = (2 + vertex.x * 2) * vertex.z + (vertex.z - 1) * 2;

	pVertex = new VERTEX_3D[g_Vertex_max];

	unsigned short* pIndex;
	pIndex = new unsigned short[g_Index_max];

	/////////////////////////////////////////////////////
	////		�o�[�e�b�N�X�o�b�t�@
	/////////////////////////////////////////////////////

	for (int z = 0; z <= vertex.z; z++)
	{
		for (int x = 0; x <= vertex.x; x++)
		{
			pVertex[z * (vertex.x + 1) + x].Position.x = x * FIELD_SIZE;
			pVertex[z * (vertex.x + 1) + x].Position.z = -z * FIELD_SIZE;
			pVertex[z * (vertex.x + 1) + x].Position.y = g_FieldHeight[z][x];
			pVertex[z * (vertex.x + 1) + x].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			pVertex[z * (vertex.x + 1) + x].TexCoord = XMFLOAT2(x, z);
			pVertex[z * (vertex.x + 1) + x].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		}
	}
	XMFLOAT3 va;
	XMFLOAT3 vb;
	XMFLOAT3 n;
	//�@���x�N�g���A-1�͒[�̒��_
	for (int z = 1; z < vertex.z - 1; z++)
	{
		for (int x = 1; x < vertex.x - 1; x++)
		{
			va.x = pVertex[(z - 1) * vertex.x + x].Position.x - pVertex[(z + 1) * vertex.x + x].Position.x;
			va.y = pVertex[(z - 1) * vertex.x + x].Position.y - pVertex[(z + 1) * vertex.x + x].Position.y;
			va.z = pVertex[(z - 1) * vertex.x + x].Position.z - pVertex[(z + 1) * vertex.x + x].Position.z;
			vb.x = pVertex[z * vertex.x + (x + 1)].Position.x - pVertex[z * vertex.x + (x - 1)].Position.x;
			vb.y = pVertex[z * vertex.x + (x + 1)].Position.y - pVertex[z * vertex.x + (x - 1)].Position.y;
			vb.z = pVertex[z * vertex.x + (x + 1)].Position.z - pVertex[z * vertex.x + (x - 1)].Position.z;
			//n = va�~vb(�O��)
			n = OuterProduct(va, vb);
			float length = sqrtf(n.x * n.x + n.y * n.y + n.z * n.z);
			//���K��(�m�[�}���C�Y)
			n.x = n.x / length;
			n.y = n.y / length;
			n.z = n.z / length;
			pVertex[z * vertex.x + x].Normal = n;
		}
	}


	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(VERTEX_3D) * g_Vertex_max;	// �\���̂̃T�C�Y
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// ���o�b�t�@�̐ݒ�
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = pVertex;	// �ŏ��̒��_���i�[
		CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
		delete[] pVertex;
	}


	/////////////////////////////////////////////////////
	////		�C���f�b�N�X�o�b�t�@
	/////////////////////////////////////////////////////
	int i = 0;
	for (int z = 0; z < vertex.z; z++)
	{
		for (int x = 0; x <= vertex.x; x++)
		{
			pIndex[i] = (z + 1) * (vertex.x + 1) + x;
			i++;
			pIndex[i] = (z) * (vertex.x + 1) + x;
			i++;
		}
		if (z != vertex.z - 1)
		{
			pIndex[i] = pIndex[i - 1];
			i++;
			pIndex[i] = (z + 2) * (vertex.x + 1) + 0;
			i++;
		}
	}

	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(unsigned short) * g_Index_max;	// �\���̂̃T�C�Y
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;	// ���o�b�t�@�̐ݒ�
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = pIndex;	// �ŏ��̒��_���i�[
		CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_IndexBuffer);
		delete[] pIndex;

	}
		m_Texture = new CTexture();
		m_Texture->Load("asset/field004.tga");	// tga�t�H�[�}�b�g�̃��`�����l���t�����k���Ȃ��B

}

void CMesh_Field::Uninit()
{
	m_VertexBuffer->Release();
	m_Texture->Unload();
	delete m_Texture;
}

void CMesh_Field::Update()
{
}


void CMesh_Field::Draw()
{
	//UINT stride = sizeof(VERTEX_3D);
	//UINT offset = 0;
	//CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);	//	���_�o�b�t�@��ݒ� 9����SetVertexBuffer
	CRenderer::SetVertexBuffers(m_VertexBuffer);
	CRenderer::SetIndexBuffer(m_IndexBuffer);
	CRenderer::SetTexture(m_Texture);	// �e�N�X�`���ݒ�
	XMMATRIX world;
	world = XMMatrixScaling(1.0f, 1.0f, 1.0f);		//�g��k��
	world *= XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);		//��]
	world *= XMMatrixTranslation(0.0f, 0.0f, 0.0f);		//�ړ�
	CRenderer::SetWorldMatrix(&world);
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);	//	�g�|���W�ݒ�	���g�|���W = �ǂ�����Đ������Ԃ��B���̏ꍇ��TRIANGLESTRIP�^�Ō���
	CRenderer::GetDeviceContext()->DrawIndexed(g_Index_max, 0,0);	//	�|���S���`��

}

float CMesh_Field::GetHeight(XMFLOAT3 Position)
{
	int x, z;
	XMFLOAT3 p0, p1, p2, v01, v02, n, v, hp, va, vb;
	float dp0n, dvn, dpn, t;
	v = XMFLOAT3(0.0f, -10.0f, 0.0f);
	x = Position.x / FIELD_SIZE;
	z = -Position.z / FIELD_SIZE;

	va.x = pVertex[(z + 1) * 5 + (x + 1)].Position.x - pVertex[z * 5 + x].Position.x;
	va.y = pVertex[(z + 1) * 5 + (x + 1)].Position.y - pVertex[z * 5 + x].Position.x;
	va.z = pVertex[(z + 1) * 5 + (x + 1)].Position.z - pVertex[z * 5 + x].Position.y;
	vb.x = Position.x - pVertex[z * 5 + x].Position.x;
	vb.y = Position.y - pVertex[z * 5 + x].Position.y;
	vb.z = Position.z - pVertex[z * 5 + x].Position.z;

	if (va.z*vb.x - va.x*vb.z > 0.0f)
	{
		p0 = pVertex[(z + 1) * 5 + x].Position;
		p1 = pVertex[z * 5 + x].Position;
		p2 = pVertex[(z + 1) * 5 + (x + 1)].Position;
	}
	else
	{
		p0 = pVertex[z * 5 + (x + 1)].Position;
		p1 = pVertex[(z + 1)* 5 + (x + 1)].Position;
		p2 = pVertex[(z * 5 + x)].Position;
	}

	//v01 = p1 - p0;
	v01.x = p1.x - p0.x;
	v01.y = p1.y - p0.y;
	v01.z = p1.z - p0.z;
	//v02 = p2 - p0;
	v02.x = p2.x - p0.x;
	v02.y = p2.y - p0.y;
	v02.z = p2.z - p0.z;
	//n = v01�~v02;
	n = OuterProduct(v01, v02);
	//dvn = v�En;
	dvn = InnerProduct(v, n);
	//dp0n = p0�En;
	dp0n = InnerProduct(p0, n);
	//dpn = Position�En;
	dpn = InnerProduct(Position, n);
	//t = (dp0n - dpn) / dvn;
	t = (dp0n - dpn) / dvn;
	hp.y = Position.y + v.y * t;
	return hp.y;
}

XMFLOAT3 CMesh_Field::OuterProduct(XMFLOAT3 v1, XMFLOAT3 v2)
{
	XMFLOAT3 v;
	v.x = v1.y * v2.z - v1.z * v2.y;
	v.y = v1.z * v2.x - v1.x * v2.z;
	v.z = v1.x * v2.y - v1.y * v2.x;
	return v;
}

float CMesh_Field::InnerProduct(XMFLOAT3 v1, XMFLOAT3 v2)
{
	float rad;
	rad = v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
	return rad;
}
