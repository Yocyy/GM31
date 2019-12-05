#include <random>



#include "main.h"
#include "stb-texture.h"
#include "renderer.h"
#include "game_object.h"
#include "model.h"
#include "manager.h"
#include "scene.h"
#include "field.h"
#include "input.h"
#include "ball.h"
#include "camera.h"


void CBall::Init()
{
	m_Quaternion = XMQuaternionIdentity();
	circle = new CIRCLE;
	m_Model = new CModel;
	flag_move = false;
	m_Position = XMFLOAT3(0.0f, 1.0f, 5.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);	//float(rand() % 10)
	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);

	//À•W“Çž
	{
		VECTOR3 vec;
		std::ifstream ifs("JSON/ball/BallData.json");//ŒÄ‚Ño‚µæ
		if (ifs)
		{
		cereal::JSONInputArchive inArchive(ifs);
		inArchive(vec);
		m_Position.x = vec.x;
		m_Position.y = vec.y;
		m_Position.z = vec.z;
		}
		//—áŠOƒXƒ[
	}
	//	“–‚½‚è”»’è
	circle->radius = BALL_RADIUS;

	m_Model->Load("asset/miku_01.obj");
}

void CBall::Draw()
{
	CCamera* camera;
	camera = CManager::GetScene()->GetGameObject<CCamera>(Layer3D_CAMERA);
	if (camera->GetVisibility(m_Position, BALL_RADIUS) == false)
	{
		return;
	}

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
	//‘—Mƒf[ƒ^‚ð•Û‘¶
	VECTOR3 vec;
	vec.x = m_Position.x;
	vec.y = m_Position.y;
	vec.z = m_Position.z;
	{
		std::ofstream ofs("JSON/ball/BallData.json");//•Û‘¶æ
		cereal::JSONOutputArchive outArchive(ofs);
		outArchive(vec);
	}

	m_Model->Unload();
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

	CField* m_Field = CManager::GetScene()->GetGameObject<CField>(2);
	m_Position.y = m_Field->GetHeight(m_Position) + 0.5f;
	circle->Pos = m_Position;
}