#include "main.h"
#include "stb-texture.h"
#include "renderer.h"
#include "game_object.h"
#include "model.h"
#include "manager.h"
#include "scene.h"
#include "Shader.h"
#include "model.h"
#include "camera.h"
#include "m4a1.h"
#include "player.h"
#include "scene.h"
#include "input.h"
#include <random>

void CM4A1::Init()
{
	circle = new CIRCLE;
	m_Model = new CModelAnimation();
	flag_move = false;
	m_Position = XMFLOAT3(-7, 0.0f, 5.0f);
	m_Rotation = XMFLOAT3(0.0f, 3.0f, 0.0f);	//float(rand() % 10)
	m_Scale = XMFLOAT3(0.1f, 0.1f, 0.1f);
	circle->radius = m_kCircleSize;
	m_Diffuse = COLOR(1, 0, 0, 0);
	m_Emission = COLOR(1, 1, 1, 1);
	m_SpecularColor = COLOR(1, 0, 0, 1);
	m_Shininess = 20;

	m_Model->Load("asset/MODEL/M4A1/m4a1_s.obj");

	m_Shader = new CShader();
	m_Shader->Init(VS_CSO::Shader_3D, PS_CSO::Shader_3D);
}

void CM4A1::Draw()
{

	m_Material.Diffuse = m_Diffuse;
	m_Material.Emission = m_Emission;
	m_Material.SpecularColor = m_SpecularColor;
	m_Material.Shininess = m_Shininess;
	m_Shader->SetMaterial(m_Material);
	// マトリクス設定
	XMMATRIX world;
	world = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

	XMFLOAT4X4 world4x4;
	XMStoreFloat4x4(&world4x4, world);
	m_Shader->SetWorldMatrix(&world4x4);
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	CCamera* camera;
	camera = CManager::GetScene()->GetGameObject<CCamera>(Layer3D_CAMERA);
	XMFLOAT4X4 viewmatrix4x4;
	XMStoreFloat4x4(&viewmatrix4x4, camera->Get_Camera_ViewMatrix());
	m_Shader->SetViewMatrix(&viewmatrix4x4);

	XMFLOAT4X4 promatrix4x4;
	XMStoreFloat4x4(&promatrix4x4, camera->Get_Camera_Projection());
	m_Shader->SetProjectionMatrix(&promatrix4x4);

	m_Shader->SetCameraPosition(&camera->Get_Camera_Position4f());

	m_Shader->Set();
	m_Model->Draw(world);
}

void CM4A1::Uninit()
{
	m_Model->Unload();
	delete m_Model;
	m_Shader->Uninit();
	delete m_Shader;
}

void CM4A1::Update()
{
	if (CInput::GetKeyPress('F')) {
		m_Rotation.y++;
	}
	CScene* scene = CManager::GetScene();
	//m_Rotation = scene->GetGameObject<CCamera>(Layer3D_CAMERA)->Get_Camera_Rotation();

	//m_Position = scene->GetGameObject<CPlayer>(Layer3D_MODEL)->Get_Player_Position();

	XMFLOAT3 front = scene->GetGameObject<CPlayer>(Layer3D_MODEL)->Get_Player_Front();
	XMVECTOR vec = XMLoadFloat3(&front);
	XMVector3Normalize(vec);
	vec *= 2;
	XMStoreFloat3(&front, vec);
	m_Position = XMFLOAT3(m_Position.x + front.x, m_Position.y + front.y, m_Position.z + front.z);
	//CScene* scene = CManager::GetScene();
	//CCamera* m_Camera = scene->GetGameObject<CCamera>(Layer3D_CAMERA);
	//XMFLOAT4X4* ss = (XMFLOAT4X4*)&m_Camera->Get_Camera_ViewMatrix();

	//m_Front.y = -ss->_31;	//行列の31,32,33でCameraのZForward,41,42,43でCameraのPosition
	//m_Front.x = ss->_32;
	////m_Front.z = ss->_33;

	//m_Rotation = m_Front;

	//circle->Pos = m_Position;
	
}

XMFLOAT3 CM4A1::GetPosition()
{
	return m_Position;
}

void CM4A1::SetPosition(XMFLOAT3 position) {
	m_Position = position;
	CScene* scene = CManager::GetScene();
	CCamera* m_Camera = scene->GetGameObject<CCamera>(Layer3D_CAMERA);
	XMFLOAT4X4* ss = (XMFLOAT4X4*)&m_Camera->Get_Camera_ViewMatrix();
	position.y = -ss->_31;	//行列の31,32,33でCameraのZForward,41,42,43でCameraのPosition
	position.x = ss->_32;
	position.z = ss->_33;

	m_Position.x += position.x;
	//m_Position.y += position.y;
	m_Position.z += position.z;
}