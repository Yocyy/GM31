#include "main.h"
#include "scene.h"
#include "manager.h"
#include "stb-texture.h"
#include "renderer.h"
#include "game_object.h"
#include "camera.h"
#include "bullet_billboard.h"
#include "Shader.h"

//-------------------------------------------------------------------//
//							構造体定義								 //
//-------------------------------------------------------------------//

void CBullet_Billboard::Init()
{
	Count = 0;
	m_Scale = XMFLOAT3(0.01f, 0.01f, 0.01f);

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

	m_Ambient = COLOR(1, 1, 1, 1);
	m_Diffuse = COLOR(1, 1, 1, 1);
	m_Emission = COLOR(1, 1, 1, 1);
	m_SpecularColor = COLOR(1, 1, 1, 1);
	m_Shininess = 20;

	m_Shader = new CShader();
	m_Shader->Init(VS_CSO::Shader_3D, PS_CSO::Shader_3D);
}

void CBullet_Billboard::Update()
{
	////サイズ
	m_Scale.x *= 0.95f;
	m_Scale.y *= 0.95f;

	//カウント
	Count++;
	if (Count >= 20)
	{
		CManager::GetScene()->DestroyGameObject(this);
	}

	XMFLOAT3 CameraPos = CManager::GetScene()->GetGameObject<CCamera>(Layer3D_CAMERA)->Get_Camera_Position();
	//カメラと自分の距離ベクトル
	m_Vec = XMFLOAT3(m_Position.x - CameraPos.x, m_Position.y - CameraPos.y, m_Position.z - CameraPos.z);
	//求めたベクトルの大きさ
	m_VecLen = sqrt(std::pow(m_Vec.x, 2) + std::pow(m_Vec.y, 2) + std::pow(m_Vec.z, 2));
}

/*---------- ビルボード描画 ----------*/
void CBullet_Billboard::Draw()
{

	m_Material.Diffuse = m_Diffuse;
	m_Material.Emission = m_Emission;
	m_Material.SpecularColor = m_SpecularColor;
	m_Material.Shininess = m_Shininess;
	m_Shader->SetMaterial(m_Material);
	CCamera* m_Camera = CManager::GetScene()->GetGameObject<CCamera>(Layer3D_CAMERA);
	XMMATRIX invView = m_Camera->Get_Camera_ViewMatrix();

	XMMATRIX world, rot;

	rot = XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);		//回転
	XMFLOAT4X4* ss = (XMFLOAT4X4*)&invView;
	ss->_41 = 0.0f;
	ss->_42 = 0.0f;
	ss->_43 = 0.0f;
	invView = XMMatrixInverse(nullptr, invView);

	rot *= invView;
	world = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);		//拡大縮小
	world *= rot;
	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);	//	頂点バッファを設定 9だとSetVertexBuffer
	CRenderer::SetTexture(m_Texture);	// テクスチャ設定

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

	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);	//	トポロジ設定	※トポロジ = どうやって線を結ぶか。この場合はTRIANGLESTRIP型で結ぶ
	CRenderer::GetDeviceContext()->Draw(4, 0);	//	ポリゴン描画
}

void CBullet_Billboard::Uninit()
{
	m_VertexBuffer->Release();
	m_Shader->Uninit();
	delete m_Shader;
}

void CBullet_Billboard::Bill_Create(XMFLOAT3 Position,CStbTexture* StbTexture)
{
	Count = 0;
	m_Position = Position;
	m_Texture = StbTexture;
}
