//#include <random>
//
//
//
//#include "main.h"
//#include "texture.h"
//#include "renderer.h"
//#include "game_object.h"
//#include "model.h"
//#include "manager.h"
//#include "scene.h"
//#include "input.h"
//#include "PointLight.h"
//#include "camera.h"
//
//
//void CBall::Init()
//{
//	m_Quaternion = XMQuaternionIdentity();
//	m_Model = new CModel;
//	m_Position = XMFLOAT3(0.0f, 1.0f, 5.0f);
//	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
//	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
//
//	m_Model->Load("asset/miku_01.obj");
//}
//
//void CBall::Draw()
//{
//	// マトリクス設定
//	XMMATRIX world;
//	world = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
//	world *= XMMatrixRotationQuaternion(m_Quaternion);
//	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
//	CRenderer::SetWorldMatrix(&world);
//	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//
//	//ライト設定
//	CScene* scene = CManager::GetScene();
//	ConstantBuffer cb;
//	ZeroMemory(&cb, sizeof(cb));
//	XMStoreFloat4x4(&cb.world,world);	//ワールド座標
//	XMStoreFloat4x4(&cb.view, scene->GetGameObject<CCamera>(Layer3D_CAMERA)->Get_Camera_ViewMatrix());	//ビュー行列
//	XMStoreFloat4x4(&cb.projection, scene->GetGameObject<CCamera>(Layer3D_CAMERA)->Get_Camera_Projection());	//プロジェクション行列
//	cb.light = XMFLOAT4(0,0,0,0);
//	cb.attenuation = XMFLOAT4(10,10,10,10);
//	CRenderer::SetPointLight(cb);
//
//	m_Model->Draw();
//}
//
//void CBall::Uninit()
//{
//	m_Model->Unload();
//}
//
//void CBall::Update()
//{
//	if (CInput::GetKeyPress(VK_UP)) {
//		m_Position.z += MoveSpeed;
//	}
//	if (CInput::GetKeyPress(VK_DOWN)) {
//		m_Position.z -= MoveSpeed;
//	}
//	if (CInput::GetKeyPress(VK_RIGHT)) {
//		m_Position.x += MoveSpeed;
//	}
//	if (CInput::GetKeyPress(VK_LEFT)) {
//		m_Position.x -= MoveSpeed;
//	}
//}