
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
	//マウスの現在の座標を取得する
	GetCursorPos(&pt);

	////マウスの位置を+10移動する
	////SetCursorPos(pt.x + 10, pt.y + 10);

	////マウスの左ボタンを押す　右はMOUSEEVENTF_RIGHTDOWN　中央はMOUSEEVENTF_MIDDLEDOWN
	//mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);

	////マウスの左ボタンを離す
	//mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

	////ホイールを下向きに回す
	//mouse_event(MOUSEEVENTF_WHEEL, 0, 0, -1, 0);

	////ホイールを上向きに回す
	//mouse_event(MOUSEEVENTF_WHEEL, 0, 0, 1, 0);

	//文字を入力
	//HWND hWnd = WindowFromPoint(pt);
	//SendMessage(hWnd,WM_SETTEXT,0,(LPARAM)"文字列");


	////////////////////////////////////////////////////////
////				移 動
////////////////////////////////////////////////////////

	CScene* scene = CManager::GetScene();

	//ウィンドウ座標からウィンドウ中央座標を取得
	RECT rect;
	GetWindowRect(GetWindow(),&rect);
	float xd = rect.left + SCREEN_WIDTH / 2;
	float yd = rect.top + SCREEN_HEIGHT / 2;

	// カメラ回転
	float rotate_y = pt.x - xd;
	m_Rotation.y += rotate_y / 100.0f;
	float rotate_x = pt.y - yd;
	m_Rotation.x += rotate_x / 100.0f;
	// カメラの移動範囲設定
	m_Rotation.x = m_Rotation.x < 1.0f ? m_Rotation.x > -1.0f ? m_Rotation.x : -1.0f :1.0f;
	// プレイヤー座標を取得
	if(m_Player)
		m_Position = m_Player->Get_Player_Position();
	// カーソルを画面中央に戻す
	SetCursorPos(xd, yd);

	///////////////////////////////////////////////////////
	////				回 転
	///////////////////////////////////////////////////////
	if (rotate_y != 0) {
		// Qキーが押されている時の処理
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

	// ビューポート設定
	D3D11_VIEWPORT dxViewport;
	dxViewport.Width = (float)(m_Viewport.right - m_Viewport.left);
	dxViewport.Height = (float)(m_Viewport.bottom - m_Viewport.top);
	dxViewport.MinDepth = 0.0f;
	dxViewport.MaxDepth = 1.0f;
	dxViewport.TopLeftX = (float)m_Viewport.left;
	dxViewport.TopLeftY = (float)m_Viewport.top;

	CRenderer::GetDeviceContext()->RSSetViewports(1, &dxViewport);



	// ビューマトリクス設定
	InvViewMatrix = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	InvViewMatrix *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

	XMVECTOR det;
	ViewMatrix = XMMatrixInverse(&det, InvViewMatrix);
	XMStoreFloat4x4(&m_InvViewMatrix, InvViewMatrix);

	CRenderer::SetViewMatrix(&ViewMatrix);

	// プロジェクションマトリクス設定
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
	viewPos = XMVector3TransformCoord(worldPos, ViewMatrix);		//座標変換
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

