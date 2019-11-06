#include "main.h"
#include "texture.h"
#include "renderer.h"
#include "game_object.h"
#include "model.h"
#include "manager.h"
#include "scene.h"
#include "field.h"
#include "input.h"
#include "ball.h"
#include <random>

void CBall::Init()
{
	m_Quaternion = XMQuaternionIdentity();
	circle = new CIRCLE;
	m_Model = new CModel;
	flag_move = false;
	m_Position = XMFLOAT3(float(rand() % 10), 1.0f, 5.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);	//float(rand() % 10)
	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	circle->radius = BALL_RADIUS;

	m_Model->Load("asset/miku_01.obj");
}

void CBall::Draw()
{
	// ƒ}ƒgƒŠƒNƒXÝ’è
	XMMATRIX world;
	world = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world *= XMMatrixRotationQuaternion(m_Quaternion);
	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	CRenderer::SetWorldMatrix(&world);
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_Model->Draw();
}

void CBall::Uninit()
{
	m_Model->Unload();
	CScene* scene = CManager::GetScene();
}

void CBall::Update()
{
	if (CInput::GetKeyPress(VK_UP)) {
		XMFLOAT3 vx = XMFLOAT3(1, 0, 0);
		XMVECTOR axis = XMLoadFloat3(&vx);	//Ž²
		XMVECTOR rotation = XMQuaternionRotationAxis(axis, RotationSpeed);	//Ž²‰ñ“]
		m_Quaternion = XMQuaternionMultiply(m_Quaternion, rotation);	//‰ñ“]Š®—¹
		m_Quaternion = XMQuaternionNormalize(m_Quaternion);

		m_Position.z += MoveSpeed;
	}
	if (CInput::GetKeyPress(VK_DOWN)) {
		XMFLOAT3 vx = XMFLOAT3(-1, 0, 0);
		XMVECTOR axis = XMLoadFloat3(&vx);	//Ž²
		XMVECTOR rotation = XMQuaternionRotationAxis(axis, RotationSpeed);	//Ž²‰ñ“]
		m_Quaternion = XMQuaternionMultiply(m_Quaternion, rotation);	//‰ñ“]Š®—¹
		m_Quaternion = XMQuaternionNormalize(m_Quaternion);

		m_Position.z -= MoveSpeed;
	}
	if (CInput::GetKeyPress(VK_RIGHT)) {
		XMFLOAT3 vz = XMFLOAT3(0, 0, -1);
		XMVECTOR axis = XMLoadFloat3(&vz);	//Ž²
		XMVECTOR rotation = XMQuaternionRotationAxis(axis, RotationSpeed);	//Ž²‰ñ“]
		m_Quaternion = XMQuaternionMultiply(m_Quaternion, rotation);	//‰ñ“]Š®—¹
		m_Quaternion = XMQuaternionNormalize(m_Quaternion);

		m_Position.x += MoveSpeed;
	}
	if (CInput::GetKeyPress(VK_LEFT)) {
		XMFLOAT3 vz = XMFLOAT3(0, 0, 1);
		XMVECTOR axis = XMLoadFloat3(&vz);	//Ž²
		XMVECTOR rotation = XMQuaternionRotationAxis(axis, RotationSpeed);	//Ž²‰ñ“]
		m_Quaternion = XMQuaternionMultiply(m_Quaternion, rotation);	//‰ñ“]Š®—¹
		m_Quaternion = XMQuaternionNormalize(m_Quaternion);

		m_Position.x -= MoveSpeed;
	}

	CField* m_Field = CManager::GetScene()->GetGameObject<CField>(1);
	m_Position.y = m_Field->GetHeight(m_Position) + 0.5f;
	circle->Pos = m_Position;
}