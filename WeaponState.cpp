#include "main.h"
#include "manager.h"
#include "scene.h"
#include "game_object.h"
#include "BulletManager.h"
#include "audio_clip.h"
#include "camera.h"
#include "player.h"
#include "input.h"
#include "renderer.h"
#include "Shader.h"
#include "modelAnimation.h"
#include "WeaponState.h"

void KNIFE::Action()
{
	//ナイフモーション
	m_AudioClip->Play();
}

void KNIFE::Peak()
{
}

void KNIFE::Reload()
{
}

void KNIFE::Init()
{
	this->m_Model = new CModelAnimation();
	this->m_Rotation = XMFLOAT3(0.0f, 3.0f, 0.0f);	//float(rand() % 10)
	this->m_Scale = XMFLOAT3(0.03f, 0.03f, 0.03f);
	//this->m_Diffuse = COLOR(1, 0, 0, 0);
	//this->m_Emission = COLOR(1, 1, 1, 1);
	//this->m_SpecularColor = COLOR(1, 0, 0, 1);
	//this->m_Shininess = 20;
	this->m_AudioClip = new CAudioClip();
	this->m_AudioClip->Load("asset/sound/SE/shotsound_001.wav");

	this->m_Model->Load("asset/MODEL/KNIFE/m9 bayonet.obj");
	this->m_Shader = new CShader();
	this->m_Shader->Init(VS_CSO::Shader_3D, PS_CSO::Shader_3D);

}

void KNIFE::Update()
{
	CScene* scene = CManager::GetScene();
	m_Rotation = scene->GetGameObject<CCamera>(Layer3D_CAMERA)->Get_Camera_Rotation();

	m_Position = scene->GetGameObject<CPlayer>(Layer3D_MODEL)->Get_Player_Position();

	XMFLOAT3 front = scene->GetGameObject<CPlayer>(Layer3D_MODEL)->Get_Player_Front();
	XMVECTOR vec = XMLoadFloat3(&front);
	XMVector3Normalize(vec);
	vec *= 2;
	XMStoreFloat3(&front, vec);
	m_Position = XMFLOAT3(m_Position.x + front.x, m_Position.y + front.y, m_Position.z + front.z);
}

void KNIFE::Draw()
{
	if (!this->m_CurrentWeapon) return;

	//m_Material.Diffuse = m_Diffuse;
	//m_Material.Emission = m_Emission;
	//m_Material.SpecularColor = m_SpecularColor;
	//m_Material.Shininess = m_Shininess;
	//m_Shader->SetMaterial(m_Material);
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

void KNIFE::Uninit()
{
	this->m_Model->Unload();
	delete this->m_Model;
	this->m_Shader->Uninit();
	delete this->m_Shader;
	this->m_AudioClip->Unload();
	delete this->m_AudioClip;
}

void AK::Action()
{
	if (this->m_BulletNum > 0)
	{
		m_AudioClip->Play();
		this->m_BulletNum--;

		CManager::GetScene()->GetGameObject<CBulletManager>(Layer3D_Manager)->CreateBullet(XMFLOAT3(0, 0, 0), XMFLOAT3(0, 0, 1), BULLET_TYPE::zero);
	}
}

void AK::Peak()
{
	CManager::GetScene()->GetGameObject<CCamera>(Layer3D_CAMERA)->ScopeEnable();
}

void AK::Reload()
{
	if (this->m_BulletNum != this->m_kBulletMaxNum)
	{
		//リロードモーション

		this->m_BulletNum = this->m_kBulletMaxNum;
	}
}

void AK::Init()
{
	this->m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);	//float(rand() % 10)
	this->m_Scale = XMFLOAT3(0.1f, 0.1f, 0.1f);
	this->m_AudioClip = new CAudioClip();
	this->m_AudioClip->Load("asset/sound/SE/shotsound_001.wav");
	this->m_Model = new CModelAnimation();
	this->m_Model->Load("asset/MODEL/45ACP/Handgun_Game_Blender Gamer Engine.obj");
	this->m_Shader = new CShader();
	this->m_Shader->Init(VS_CSO::Shader_3D, PS_CSO::Shader_3D);
	this->m_BulletNum = this->m_kBulletMaxNum;
}

void AK::Update()
{
	CScene* scene = CManager::GetScene();
	m_Rotation = scene->GetGameObject<CCamera>(Layer3D_CAMERA)->Get_Camera_Rotation();

	m_Position = scene->GetGameObject<CPlayer>(Layer3D_MODEL)->Get_Player_Position();

	XMFLOAT3 front = scene->GetGameObject<CPlayer>(Layer3D_MODEL)->Get_Player_Front();
	XMVECTOR vec = XMLoadFloat3(&front);
	XMVector3Normalize(vec);
	vec *= 2;
	XMStoreFloat3(&front, vec);
	m_Position = XMFLOAT3(m_Position.x + front.x, m_Position.y + front.y, m_Position.z + front.z);
}

void AK::Draw()
{
	if (!this->m_CurrentWeapon) return;

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

void AK::Uninit()
{
	this->m_Model->Unload();
	delete this->m_Model;
	this->m_Shader->Uninit();
	delete this->m_Shader;
	this->m_AudioClip->Unload();
	delete this->m_AudioClip;
}

void M4A1::Action()
{
	if (this->m_BulletNum > 0)
	{
		m_AudioClip->Play();
		this->m_BulletNum--;
		CManager::GetScene()->GetGameObject<CBulletManager>(Layer3D_Manager)->CreateBullet(XMFLOAT3(0, 0, 0), XMFLOAT3(0, 0, 1), BULLET_TYPE::one);
	}
}

void M4A1::Peak()
{
	CManager::GetScene()->GetGameObject<CCamera>(Layer3D_CAMERA)->ScopeEnable();
}

void M4A1::Reload()
{
	if (this->m_BulletNum != this->m_kBulletMaxNum)
	{
		//リロードモーション

		this->m_BulletNum = this->m_kBulletMaxNum;
	}
}

void M4A1::Init()
{
	this->m_Model = new CModelAnimation();
	this->m_Rotation = XMFLOAT3(0.0f, 3.0f, 0.0f);	//float(rand() % 10)
	this->m_Scale = XMFLOAT3(0.1f, 0.1f, 0.1f);
	//this->m_Diffuse = COLOR(1, 0, 0, 0);
	//this->m_Emission = COLOR(1, 1, 1, 1);
	//this->m_SpecularColor = COLOR(1, 0, 0, 1);
	//this->m_Shininess = 20;

	this->m_AudioClip = new CAudioClip();
	this->m_AudioClip->Load("asset/sound/SE/shotsound_001.wav");

	this->m_Model->Load("asset/MODEL/M4A1/m4a1_s.obj");
	this->m_Shader = new CShader();
	this->m_Shader->Init(VS_CSO::Shader_3D, PS_CSO::Shader_3D);

	this->m_BulletNum = this->m_kBulletMaxNum;
}

void M4A1::Update()
{
	CScene* scene = CManager::GetScene();
	m_Rotation = scene->GetGameObject<CCamera>(Layer3D_CAMERA)->Get_Camera_Rotation();

	m_Position = scene->GetGameObject<CPlayer>(Layer3D_MODEL)->Get_Player_Position();

	XMFLOAT3 front = scene->GetGameObject<CPlayer>(Layer3D_MODEL)->Get_Player_Front();
	XMVECTOR vec = XMLoadFloat3(&front);
	XMVector3Normalize(vec);
	vec *= 2;
	XMStoreFloat3(&front, vec);
	m_Position = XMFLOAT3(m_Position.x + front.x, m_Position.y + front.y, m_Position.z + front.z);
}

void M4A1::Draw()
{
	if (!this->m_CurrentWeapon) return;

	//m_Material.Diffuse = m_Diffuse;
//m_Material.Emission = m_Emission;
//m_Material.SpecularColor = m_SpecularColor;
//m_Material.Shininess = m_Shininess;
//m_Shader->SetMaterial(m_Material);
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

void M4A1::Uninit()
{
	this->m_Model->Unload();
	delete this->m_Model;
	this->m_Shader->Uninit();
	delete this->m_Shader;
	this->m_AudioClip->Unload();
	delete this->m_AudioClip;
}
