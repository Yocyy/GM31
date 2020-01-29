//=============================================================================
//
// スカイドーム内処理 [skydome.cpp]
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
// スカイドームの初期化
//=============================================================================
void CSkydome::Init()
{
	//テクスチャ設定
	m_Texture = new CStbTexture();
	m_Texture->Load("asset/field004.tga");

	//外積
	XMVECTOR cross;

	//頂点、indexデータの最大値取得
	g_Vertex_max = (surface_num + 1) * (surface_num + 1);
	g_Index_max = (2 + surface_num * 2) * surface_num + (surface_num - 1) * 2;



	//バッファ初期化 
	//g_pDevice = MyDirect3D_GetDevice();
	//g_pDevice->CreateVertexBuffer(sizeof(MESH) * g_Vertex_max, D3DUSAGE_WRITEONLY, FVF_VERTEX3D, D3DPOOL_MANAGED, &g_VertexBuffer, NULL);
	//g_pDevice->CreateIndexBuffer(sizeof(WORD) * g_Index_max, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_IndexBuffer, NULL);
	//CScene* scene = CManager::GetScene();
	//CRenderer::GetDevice()->CreateBuffer()
	//m_VertexBuffer



	//頂点バッファの取得 
	SKYMESH *pVertex;
	pVertex = new SKYMESH();
	for (int z = 0; z <= surface_num; z++)
	{
		for (int x = 0; x <= surface_num; x++)
		{
			//座標
			pVertex[z * (surface_num + 1) + x].Pos.x = cos(XMConvertToRadians((360.0f / surface_num) * x)) * sin(XMConvertToRadians((90.f / surface_num) * z)) * radius;
			pVertex[z * (surface_num + 1) + x].Pos.z = -sin(XMConvertToRadians((360.0f / surface_num) * x)) * sin(XMConvertToRadians((90.f / surface_num) * z)) * radius;
			pVertex[z * (surface_num + 1) + x].Pos.y = cos(XMConvertToRadians((90.0f / surface_num) * z)) * radius;

			//外積からの法線
			cross = XMVector3Cross(XMLoadFloat3(&pVertex[z * (surface_num + 1) + x].Pos), XMLoadFloat3(&pVertex[z * (surface_num + 1) + x].Pos));
			XMStoreFloat3(&pVertex[z * (surface_num + 1) + x].NVect,cross);

			//uv設定
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


	//indexバッファの取得
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
// スカイドームの終了処理
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
// スカイドームの描画
//=============================================================================
void CSkydome::Draw()
{
//	//--------------------------------------------------
//	//          行列宣言、単位行列化
//	//--------------------------------------------------
//
//
//	//--------------------------------------------------
//	//          行列の移動、回転、縮小式、合成
//	//--------------------------------------------------
//
//
//	//--------------------------------------------------
//	//          デバイスセッティング
//	//--------------------------------------------------
//	//デバイスへ行列を設定
//	g_pDevice->SetTransform(D3DTS_WORLD, &mtxMatrix);
//
//
//	//頂点データ描画の設定
//	g_pDevice->SetStreamSource(0, g_VertexBuffer, 0, sizeof(MESH));
//	g_pDevice->SetIndices(g_IndexBuffer);
//
//
//	//ライティング
//	g_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
//
//	//FVFの設定
//	g_pDevice->SetFVF(FVF_VERTEX3D);
//
//	//テクスチャの設定
//	g_pDevice->SetTexture(0, g_pTexture);
//
//
//	//--------------------------------------------------
//	//          描画開始
//	//--------------------------------------------------
//	g_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_Vertex_max, 0, g_Index_max - 2);
//
//
//	//--------------------------------------------------
//	//          デバイス再セッティング
//	//--------------------------------------------------



	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// インデックスバッファ設定
	CRenderer::GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R16_UINT, 0);


	// テクスチャ設定
	CRenderer::SetTexture(m_Texture);

	// マトリクス設定
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

	// プリミティブトポロジ設定
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);


	// ポリゴン描画
	//CRenderer::GetDeviceContext()->DrawIndexed(((FIELD_X * 2 + 2) * (FIELD_Z - 1) - 2), 0, 0);
}