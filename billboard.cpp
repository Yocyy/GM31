#include "main.h"
#include "scene.h"
#include "manager.h"
#include "texture.h"
#include "renderer.h"
#include "game_object.h"
#include "camera.h"
#include "billboard.h"
#include "stb-texture.h"

//-------------------------------------------------------------------//
//							構造体定義								 //
//-------------------------------------------------------------------//

void CBillboard::Init()
{
	Count = 0;

	vertex[0].Position = XMFLOAT3(-x, -y, 0.0f);		// 座標
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);			// 法線
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);	// 色
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);				//uv

	vertex[1].Position = XMFLOAT3(-x, y, 0.0f);		// 座標
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);			// 法線
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);	// 色
	vertex[1].TexCoord = XMFLOAT2(0.0f, 1.0f);				//uv

	vertex[2].Position = XMFLOAT3(x, -y, 0.0f);		// 座標
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);			// 法線
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);	// 色
	vertex[2].TexCoord = XMFLOAT2(1.0f, 0.0f);				//uv

	vertex[3].Position = XMFLOAT3(x, y, 0.0f);		// 座標
	vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);			// 法線
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);	// 色
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);				//uv

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;	// 構造体のサイズ
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// 作るバッファの設定
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;	// 最初の頂点を格納
	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

}

void CBillboard::Update()
{
	// 進行方向
	m_Position.x += MoveSpeed * m_Front.x;
	m_Position.y += MoveSpeed * m_Front.y;
	m_Position.z += MoveSpeed * m_Front.z;
	//カウント
	Count++;
	if (Count >= 60)
	{
		CManager::GetScene()->DestroyGameObject(this);
		//this->Uninit()

	}
}

/*---------- ビルボード描画 ----------*/
void CBillboard::Draw()
{

	CCamera* m_Camera = CManager::GetScene()->GetGameObject<CCamera>(Layer3D_CAMERA);
	XMMATRIX invView = m_Camera->Get_Camera_ViewMatrix();

	XMMATRIX world,rot;

	rot = XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);		//回転
	XMFLOAT4X4* ss = (XMFLOAT4X4*)&invView;
	ss->_41 = 0.0f;
	ss->_42 = 0.0f;
	ss->_43 = 0.0f;
	invView = XMMatrixInverse(nullptr, invView);

	rot *= invView;
	world = XMMatrixScaling(0.1f, 0.1f, 0.1f);		//拡大縮小
	world *= rot;
	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);	//	頂点バッファを設定 9だとSetVertexBuffer
	CRenderer::SetTexture(m_Texture);	// テクスチャ設定
	//XMMATRIX world;
	//world *= XMMatrixTranslation(g_Billboard.Position.x, g_Billboard.Position.y, g_Billboard.Position.z);		//移動
	CRenderer::SetWorldMatrix(&world);
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);	//	トポロジ設定	※トポロジ = どうやって線を結ぶか。この場合はTRIANGLESTRIP型で結ぶ
	CRenderer::GetDeviceContext()->Draw(4, 0);	//	ポリゴン描画
}

void CBillboard::Uninit()
{
	m_VertexBuffer->Release();
	m_Texture->Unload();
	delete m_Texture;
}


void CBillboard::Bill_Create(XMFLOAT3 Position, const char* FilePass)
{
	Count = 0;
	m_Position = Position;
	m_Front = XMFLOAT3(0, 0, 0);

	m_Texture = new CStbTexture();
	m_Texture->Load(FilePass);
}

void CBillboard::Bill_Create(XMFLOAT3 Position, XMFLOAT3 Front, float Speed, const char * FilePass)
{
	Count = 0;
	m_Position = Position;
	m_Front = Front;
	MoveSpeed = Speed;

	m_Texture = new CStbTexture();
	m_Texture->Load(FilePass);
}
