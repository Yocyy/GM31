
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "game_object.h"
#include "model.h"
#include "scene.h"
#include "manager.h"
#include "ShakeCamera.h"
#include "player.h"
#include "camera.h"
#include "Shader.h"


static float MoveSpeed;
void CCamera::Init()
{
	m_Shader = new CShader();
	RECT rect;
	GetWindowRect(GetWindow(), &rect);
	Center_X = rect.left + SCREEN_WIDTH / 2;
	Center_Y = rect.top + SCREEN_HEIGHT / 2;
	SetCursorPos(Center_X, Center_Y);
	MoveSpeed = 0.1f;
	m_Position = XMFLOAT3(0.0f, 10.0f, -10.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);


	m_Viewport.left = 0;
	m_Viewport.top = 0;
	m_Viewport.right = SCREEN_WIDTH;
	m_Viewport.bottom = SCREEN_HEIGHT;
	fov = 1.0f;
	aspect = NULL;
	nearZ = 1.0f;
	farZ = 1000.0f;
	m_ScopeEnable = false;
}


void CCamera::Uninit()
{
	m_Shader->Uninit();
	delete m_Shader;
}


void CCamera::Update()
{
	GetCursorPos(&pt);
	//�E�B���h�E���W����E�B���h�E�������W���擾
	RECT rect;
	GetWindowRect(GetWindow(), &rect);
	if (CInput::GetKeyTrigger('G'))
	{
		Debug_flag ^= true;
		ShowCursor(Debug_flag);
		pt.x = rect.left + SCREEN_WIDTH / 2;
		pt.y = rect.top + SCREEN_HEIGHT / 2;
	}
	if (!Debug_flag)
	{
		if (!m_Player) {
			m_Player = CManager::GetScene()->GetGameObject<CPlayer>(Layer3D_MODEL);
		}

		//�}�E�X�̌��݂̍��W���擾����


		////�}�E�X�̈ʒu��+10�ړ�����
		////SetCursorPos(pt.x + 10, pt.y + 10);

		////�}�E�X�̍��{�^���������@�E��MOUSEEVENTF_RIGHTDOWN�@������MOUSEEVENTF_MIDDLEDOWN
		//mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);

		////�}�E�X�̍��{�^���𗣂�
		//mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

		////�z�C�[�����������ɉ�
		//mouse_event(MOUSEEVENTF_WHEEL, 0, 0, -1, 0);

		////�z�C�[����������ɉ�
		//mouse_event(MOUSEEVENTF_WHEEL, 0, 0, 1, 0);

		//���������
		//HWND hWnd = WindowFromPoint(pt);
		//SendMessage(hWnd,WM_SETTEXT,0,(LPARAM)"������");


		////////////////////////////////////////////////////////
	////				�� ��
	////////////////////////////////////////////////////////

		CScene* scene = CManager::GetScene();


		 Center_X = rect.left + SCREEN_WIDTH / 2;
		 Center_Y = rect.top + SCREEN_HEIGHT / 2;

		// �J������]
		float rotate_y = pt.x - Center_X;
		m_Rotation.y += rotate_y / 100.0f;
		float rotate_x = pt.y - Center_Y;
		m_Rotation.x += rotate_x / 100.0f;
		// �J�����̈ړ��͈͐ݒ�
		m_Rotation.x = m_Rotation.x < 1.0f ? m_Rotation.x > -1.0f ? m_Rotation.x : -1.0f : 1.0f;
		// �v���C���[���W���擾
		if (m_Player)
			m_Position = m_Player->Get_Player_Position();
		// �J�[�\������ʒ����ɖ߂�
		SetCursorPos(Center_X, Center_Y);

		///////////////////////////////////////////////////////
		////				�� �]
		///////////////////////////////////////////////////////
		if (rotate_y != 0) {
			// Q�L�[��������Ă��鎞�̏���
			//m_Player->m_Rotation.y -= rotate_y;

			XMVECTOR vec;
			XMMATRIX mtx;
			XMFLOAT3 front;
			mtx = XMMatrixRotationY(rotate_y / 100);
			vec = XMVector3TransformNormal(XMLoadFloat3(&m_Player->Get_Player_Front()), mtx);
			XMStoreFloat3(&front, vec);
			m_Player->Set_Player_Front(front);

			XMFLOAT3 right;
			mtx = XMMatrixRotationY(rotate_y / 100);
			vec = XMVector3TransformNormal(XMLoadFloat3(&m_Player->Get_Player_Right()), mtx);
			XMStoreFloat3(&right, vec);
			m_Player->Set_Player_Right(right);
		}

	}
}



void CCamera::Draw()
{
	XMMATRIX	ViewMatrix;
	XMMATRIX	InvViewMatrix;
	XMMATRIX	ProjectionMatrix;

	// �r���[�|�[�g�ݒ�
	D3D11_VIEWPORT dxViewport;
	dxViewport.Width = (float)(m_Viewport.right - m_Viewport.left);
	dxViewport.Height = (float)(m_Viewport.bottom - m_Viewport.top);
	dxViewport.MinDepth = 0.0f;
	dxViewport.MaxDepth = 1.0f;
	dxViewport.TopLeftX = (float)m_Viewport.left;
	dxViewport.TopLeftY = (float)m_Viewport.top;

	CRenderer::GetDeviceContext()->RSSetViewports(1, &dxViewport);
	aspect = dxViewport.Width / dxViewport.Height;

	XMFLOAT4 CameraPos4f = XMFLOAT4(m_Position.x, m_Position.y, m_Position.x, NULL);
	m_Shader->SetCameraPosition(&CameraPos4f);
	// �r���[�}�g���N�X�ݒ�
	InvViewMatrix = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	InvViewMatrix *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

	XMVECTOR det;
	ViewMatrix = XMMatrixInverse(&det, InvViewMatrix);
	XMStoreFloat4x4(&m_InvViewMatrix, InvViewMatrix);

	//CRenderer::SetViewMatrix(&ViewMatrix);

	// �v���W�F�N�V�����}�g���N�X�ݒ�
	ProjectionMatrix = XMMatrixPerspectiveFovLH(fov, aspect, nearZ, farZ);

	//CRenderer::SetProjectionMatrix(&ProjectionMatrix);

	XMStoreFloat4x4(&m_ProjectionMatrix, ProjectionMatrix);
	XMStoreFloat4x4(&m_ViewMatrix, ViewMatrix);
}

void CCamera::Set_Player(CPlayer * player)
{
	m_Player = player;
}

XMMATRIX CCamera::Get_Camera_ViewMatrix()
{
	return  XMLoadFloat4x4(&m_ViewMatrix);
}

XMMATRIX CCamera::Get_Camera_InvViewMatrix()
{
	return XMLoadFloat4x4(&m_InvViewMatrix);
}

XMMATRIX CCamera::Get_Camera_Projection()
{
	return XMLoadFloat4x4(&m_ProjectionMatrix);
}

XMFLOAT3 CCamera::Get_Camera_Position()
{
	return m_Position;
}

XMFLOAT4 CCamera::Get_Camera_Position4f()
{
	return XMFLOAT4(m_Position.x, m_Position.y, m_Position.z, NULL);
}

XMFLOAT3 CCamera::Get_Camera_Rotation()
{
	return m_Rotation;
}

bool CCamera::GetVisibility(XMFLOAT3 Position, float Radius)
{
	XMVECTOR worldPos, viewPos, projPos;
	XMFLOAT3 projPosF;
	XMMATRIX ViewMatrix, ProjectionMatrix;

	ViewMatrix = XMLoadFloat4x4(&m_ViewMatrix);
	ProjectionMatrix = XMLoadFloat4x4(&m_ProjectionMatrix);

	worldPos = XMLoadFloat3(&Position);
	viewPos = XMVector3TransformCoord(worldPos, ViewMatrix);		//���W�ϊ�
	projPos = XMVector3TransformCoord(viewPos, ProjectionMatrix);
	XMStoreFloat3(&projPosF, projPos);
	Radius = 0.0f;
	if (-1.0f < projPosF.x+Radius && projPosF.x-Radius < 1.0f &&
		-1.0f < projPosF.y+Radius && projPosF.y-Radius < 1.0f &&
		0.0f < projPosF.z && projPosF.z < 1.0f)
	{
		return true;
	}

	return false;
}

void CCamera::ScopeEnable(void)
{
	if (fov > 0.8f)
	{
		fov *= 0.98f;
	}
	else if (fov <= 0.8f)
	{
		fov = 0.8f;
	}
}

void CCamera::ScopeIsEnable(void)
{
	if (fov < 1.0f)
	{
		fov /= 0.98f;
	}
	else if (fov >= 1.0f)
	{
		fov = 1.0f;
	}
}

