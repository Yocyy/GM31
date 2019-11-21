
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


static float MoveSpeed;
void CCamera::Init()
{
	RECT rect;
	GetWindowRect(GetWindow(), &rect);
	float xd = rect.left + SCREEN_WIDTH / 2;
	float yd = rect.top + SCREEN_HEIGHT / 2;
	SetCursorPos(xd, yd);
	MoveSpeed = 0.1f;
	m_Position = XMFLOAT3(0.0f, 10.0f, -10.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);


	m_Viewport.left = 0;
	m_Viewport.top = 0;
	m_Viewport.right = SCREEN_WIDTH;
	m_Viewport.bottom = SCREEN_HEIGHT;
	//m_Player = new CPlayer();
	//SetCursorPos(0, 0);
}


void CCamera::Uninit()
{
}


void CCamera::Update()
{
	if (!m_Player) {
		m_Player = CManager::GetScene()->GetGameObject<CPlayer>(Layer3D_MODEL);
	}

	POINT pt;
	//�}�E�X�̌��݂̍��W���擾����
	GetCursorPos(&pt);

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

	//�E�B���h�E���W����E�B���h�E�������W���擾
	RECT rect;
	GetWindowRect(GetWindow(),&rect);
	float xd = rect.left + SCREEN_WIDTH / 2;
	float yd = rect.top + SCREEN_HEIGHT / 2;

	// �J������]
	float rotate_y = pt.x - xd;
	m_Rotation.y += rotate_y / 100.0f;
	float rotate_x = pt.y - yd;
	m_Rotation.x += rotate_x / 100.0f;
	// �J�����̈ړ��͈͐ݒ�
	m_Rotation.x = m_Rotation.x < 1.0f ? m_Rotation.x > -1.0f ? m_Rotation.x : -1.0f :1.0f;
	// �v���C���[���W���擾
	if(m_Player)
		m_Position = m_Player->Get_Player_Position();
	// �J�[�\������ʒ����ɖ߂�
	SetCursorPos(xd, yd);

	///////////////////////////////////////////////////////
	////				�� �]
	///////////////////////////////////////////////////////
	if (rotate_y != 0) {
		// Q�L�[��������Ă��鎞�̏���
		//m_Player->m_Rotation.y -= rotate_y;

		XMVECTOR vec;
		XMMATRIX mtx;
		mtx = XMMatrixRotationY(rotate_y/100);
		vec = XMVector3TransformNormal(XMLoadFloat3(&m_Player->g_front), mtx);
		XMStoreFloat3(&m_Player->g_front, vec);

		mtx = XMMatrixRotationY(rotate_y/100);
		vec = XMVector3TransformNormal(XMLoadFloat3(&m_Player->g_right), mtx);
		XMStoreFloat3(&m_Player->g_right, vec);
	}

	//RECT rc;
	//rc.left = 100;
	//rc.top = 100;
	//rc.right = 110;
	//rc.bottom = 110;
	//ClipCursor(&rc);
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



	// �r���[�}�g���N�X�ݒ�
	InvViewMatrix = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	InvViewMatrix *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

	XMVECTOR det;
	ViewMatrix = XMMatrixInverse(&det, InvViewMatrix);
	XMStoreFloat4x4(&m_InvViewMatrix, InvViewMatrix);

	CRenderer::SetViewMatrix(&ViewMatrix);

	// �v���W�F�N�V�����}�g���N�X�ݒ�
	ProjectionMatrix = XMMatrixPerspectiveFovLH(1.0f, dxViewport.Width / dxViewport.Height, 1.0f, 1000.0f);

	CRenderer::SetProjectionMatrix(&ProjectionMatrix);

	XMStoreFloat4x4(&m_ProjectionMatrix, ProjectionMatrix);
	XMStoreFloat4x4(&m_ViewMatrix, ViewMatrix);
}

void CCamera::Set_Player(CPlayer * player)
{
	m_Player = player;
}

XMMATRIX CCamera::Get_Camera_InvViewMatrix()
{
	return XMLoadFloat4x4(&m_InvViewMatrix);
}

bool CCamera::GetVisibility(XMFLOAT3 Position, float Radius)
{
	XMVECTOR worldPos, viewPos, projPos;
	XMFLOAT3 projPosF;
	XMMATRIX	ViewMatrix, ProjectionMatrix;

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

