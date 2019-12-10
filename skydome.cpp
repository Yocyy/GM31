////=============================================================================
////
//// スカイドーム内処理 [skydome.cpp]
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
//// 構造体宣言
////*****************************************************************************
//
//
////*****************************************************************************
//// プロトタイプ宣言
////*****************************************************************************
//
//
////*****************************************************************************
//// グローバル変数
////*****************************************************************************
//
////-----------------------------------------------------------------------------
////-----------------------------------------------------------------------------
//
//
////=============================================================================
//// スカイドームの初期化
////=============================================================================
//void CSkydome::Init()
//{
//	//外積
//	static XMFLOAT3 cross;
//
//	//頂点、indexデータの最大値取得
//	g_Vertex_max = (surface_num + 1) * (surface_num + 1);
//	g_Index_max = (2 + surface_num * 2) * surface_num + (surface_num - 1) * 2;
//
//
//
//	//バッファ初期化 
//	//g_pDevice = MyDirect3D_GetDevice();
//	//g_pDevice->CreateVertexBuffer(sizeof(MESH) * g_Vertex_max, D3DUSAGE_WRITEONLY, FVF_VERTEX3D, D3DPOOL_MANAGED, &g_VertexBuffer, NULL);
//	//g_pDevice->CreateIndexBuffer(sizeof(WORD) * g_Index_max, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_IndexBuffer, NULL);
//
//
//	//頂点バッファの取得 
//	MESH *pVertex;
//	g_VertexBuffer->Lock(0, 0, (void**)&pVertex, 0);
//	for (int z = 0; z <= surface_num; z++)
//	{
//		for (int x = 0; x <= surface_num; x++)
//		{
//			//座標
//			pVertex[z * (surface_num + 1) + x].Pos.x = cos(D3DXToRadian((360.0f / surface_num) * x)) * sin(D3DXToRadian((90.f / surface_num) * z)) * radius;
//			pVertex[z * (surface_num + 1) + x].Pos.z = -sin(D3DXToRadian((360.0f / surface_num) * x)) * sin(D3DXToRadian((90.f / surface_num) * z)) * radius;
//			pVertex[z * (surface_num + 1) + x].Pos.y = cos(D3DXToRadian((90.0f / surface_num) * z)) * radius;
//
//			//外積からの法線
//			D3DXVec3Cross(&cross, &pVertex[z * (surface_num + 1) + x].Pos, &pVertex[z * (surface_num + 1) + x].Pos);
//			pVertex[z * (surface_num + 1) + x].NVect = cross;
//
//			//uv設定
//			pVertex[z * (surface_num + 1) + x].uv = D3DXVECTOR2((1.0f / surface_num) * x, (1.0f / surface_num) * z);
//		}
//	}
//	g_VertexBuffer->Unlock();
//
//
//	//indexバッファの取得
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
//	//テクスチャ設定
//	m_Texture->Load("");
//}
//
//
////=============================================================================
//// スカイドームの終了処理
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
//// スカイドームの描画
////=============================================================================
//void CSkydome::Draw()
//{
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
//
//
//}