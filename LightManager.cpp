#include "main.h"
#include "renderer.h"
#include "game_object.h"
#include "manager.h"
#include "scene.h"
#include "input.h"
#include "camera.h"
#include "Shader.h"
#include "LightManager.h"
#include "ball.h"
#include "manager.h"
#include "scene.h"

#include "imgui\\imgui.h"
#include "imgui\\imgui_impl_win32.h"
#include "imgui\\imgui_impl_dx11.h"
#include "imgui\\imconfig.h"
#include "imgui\\imgui_internal.h"
#include "imgui\\imstb_rectpack.h"
#include "imgui\\imstb_textedit.h"
#include "imgui\\imstb_truetype.h"

void CLightManager::Init()
{
	//imgui setup
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_Init(GetWindow());
	ImGui_ImplDX11_Init(CRenderer::GetDevice(), CRenderer::GetDeviceContext());
	ImGui::StyleColorsDark();
	ImGui_ImplDX11_NewFrame();

	m_Position = XMFLOAT4(0, 2, 0, 0);
	m_Color = COLOR(1.0f, 1.0f, 1.0f, 1.0f);	//ライトの色
	m_Pow = 1.0f;
	m_Attenuation0 = 0.1f;
	m_Attenuation1 = 0.05f;
	m_Attenuation2 = 0.07f;
	m_Type = POINT;

	m_DirLightDirection = XMFLOAT4(0.0f, -1.0f, 0.0f, 0.0f);	//ライトベクトル
	m_DirLightColor = COLOR(1.0f, 1.0f, 1.0f, 1.0f);	//ライトの色
	m_DirLightPow = 0.8f;
	m_DirLightType = DIRECTION;

	m_SpotLightDirection = XMFLOAT4(0.0f, -1.0f, 0.0f, 0.0f);
	m_SpotLightPosition = XMFLOAT4(0, 3, 10, 0);
	m_SpotLightColor = COLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_SpotLightPow = 3.0f;
	m_SpotLightAttenuation0 = 0.1f;
	m_SpotLightAttenuation1 = 0.05f;
	m_SpotLightAttenuation2 = 0.07f;
	m_SpotLightType = SPOT;


	// 定数バッファ生成
	{
		D3D11_BUFFER_DESC hBufferDesc;
		hBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		hBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		hBufferDesc.CPUAccessFlags = 0;
		hBufferDesc.MiscFlags = 0;
		hBufferDesc.StructureByteStride = sizeof(float);

		hBufferDesc.ByteWidth = sizeof(ALLLIGHT) * 4;
		CRenderer::GetDevice()->CreateBuffer(&hBufferDesc, NULL, &m_LightBuffer);
	}
}




void CLightManager::Draw()
{
	for (int i = 0; i < 2; i++)
	{
	m_Light[i].Position = m_Position;
	m_Light[i].Position.x += i * 10;
	m_Light[i].Color = m_Color;
	m_Light[i].Pow = m_Pow;
	m_Light[i].Attenuation0 = m_Attenuation0;
	m_Light[i].Attenuation1 = m_Attenuation1;
	m_Light[i].Attenuation2 = m_Attenuation2;
	m_Light[i].Type = m_Type;
	}

	m_Light[2].Direction = m_DirLightDirection;
	m_Light[2].Color = m_DirLightColor;
	m_Light[2].Pow = m_DirLightPow;
	m_Light[2].Attenuation0 = m_DirLightAttenuation0;
	m_Light[2].Attenuation1 = m_DirLightAttenuation1;
	m_Light[2].Attenuation2 = m_DirLightAttenuation2;
	m_Light[2].Type = m_DirLightType;

	m_Light[3].Direction = m_SpotLightDirection;
	m_Light[3].Position = m_SpotLightPosition;
	m_Light[3].Color = m_SpotLightColor;
	m_Light[3].Pow = m_SpotLightPow;
	m_Light[3].Attenuation0 = m_SpotLightAttenuation0;
	m_Light[3].Attenuation1 = m_SpotLightAttenuation1;
	m_Light[3].Attenuation2 = m_SpotLightAttenuation2;
	m_Light[3].Type = m_SpotLightType;

	// 定数バッファ更新
	CRenderer::GetDeviceContext()->UpdateSubresource(m_LightBuffer, 0, NULL, &m_Light, 0, 0);			//ライト

	// 定数バッファ設定
	CRenderer::GetDeviceContext()->VSSetConstantBuffers(2, 1, &m_LightBuffer);
	CRenderer::GetDeviceContext()->PSSetConstantBuffers(2, 1, &m_LightBuffer);



	//// Start the Dear ImGui frame
	//ImGui_ImplDX11_NewFrame();
	//ImGui_ImplWin32_NewFrame();
	//ImGui::NewFrame();
	//// Create imGui Test Window

	////Directional Light
	////ImGui::SetNextWindowPos(ImVec2(0, 20));
	////ImGui::SetNextWindowSize(ImVec2(300, 200));
	//ImGui::Begin("DirectionalLight");
	//ImGui::Text("(%.1f FPS)", ImGui::GetIO().Framerate);
	//ImGui::SliderFloat3("Direction.XYZ", &m_DirLightDirection.x, -1.0f, 1.0f);
	//ImGui::SliderFloat3("Color.RGB", &m_DirLightColor.r, 0.0f, 1.0f);
	//ImGui::SliderFloat("LightPow", &m_DirLightPow, 0.0f, 30.0f);
	//ImGui::End();

	////PointLight
	////ImGui::SetNextWindowPos(ImVec2(350, 20));
	////ImGui::SetNextWindowSize(ImVec2(300, 200));
	//ImGui::Begin("PointLight");
	//ImGui::SliderFloat3("Color.RGB", &m_Color.r, 0.0f, 1.0f);
	//ImGui::SliderFloat("Pow", &m_Pow, 0.0f, 30.0f);
	//ImGui::SliderFloat("Attenuation0", &m_Attenuation0, 0.0f, 1.0f);
	//ImGui::SliderFloat("Attenuation1", &m_Attenuation1, 0.0f, 1.0f);
	//ImGui::SliderFloat("Attenuation2", &m_Attenuation2, 0.0f, 1.0f);
	//
	//ImGui::End();

	////SpotLight
	////ImGui::SetNextWindowPos(ImVec2(700, 20));
	////ImGui::SetNextWindowSize(ImVec2(300, 200));
	//ImGui::Begin("SpotLight");
	//ImGui::SliderFloat3("Color.RGB", &m_SpotLightColor.r, 0.0f, 1.0f);
	////ImGui::SliderFloat3("Position.XYZ", &m_SpotLightPosition.x, 0.0f, 1.0f);
	//ImGui::SliderFloat("Pow", &m_SpotLightPow, 0.0f, 30.0f);
	//ImGui::SliderFloat("Attenuation0", &m_SpotLightAttenuation0, 0.0f, 1.0f);
	//ImGui::SliderFloat("Attenuation1", &m_SpotLightAttenuation1, 0.0f, 1.0f);
	//ImGui::SliderFloat("Attenuation2", &m_SpotLightAttenuation2, 0.0f, 1.0f);

	//ImGui::End();




	//// Assemble Together Draw Data
	//ImGui::Render();
	//// Render Draw Data
	//ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void CLightManager::Uninit()
{
	// Cleanup
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	m_LightBuffer->Release();
}

void CLightManager::Update()
{
	//XMFLOAT3 a  = CManager::GetScene()->GetGameObject<CBall>(Layer3D_MODEL)->GetPos();
	//m_Light[0].Position = XMFLOAT4(a.x,a.y,a.z,0);

	if (CInput::GetKeyPress('I')) {
		// Wキーが押されている時の処理
		m_Position.z += MoveSpeed;
	}
	if (CInput::GetKeyPress('K')) {
		// Dキーが押されている時の処理
		m_Position.z -= MoveSpeed;
	}
	if (CInput::GetKeyPress('L')) {
		// Aキーが押されている時の処理
		m_Position.x += MoveSpeed;
	}
	if (CInput::GetKeyPress('J')) {
		// Sキーが押されている時の処理
		m_Position.x -= MoveSpeed;
	}
	if (CInput::GetKeyPress('Y')) {
		// Aキーが押されている時の処理
		m_Position.y += MoveSpeed;
	}
	if (CInput::GetKeyPress('H')) {
		// Sキーが押されている時の処理
		m_Position.y -= MoveSpeed;
	}



	if (CInput::GetKeyPress('Z')) {
		XMVECTOR vec;
		XMMATRIX mtx;
		mtx = XMMatrixRotationX(m_RotationSpeed);
		vec = XMVector3TransformNormal(XMLoadFloat3(&m_Front), mtx);
		XMStoreFloat3(&m_Front, vec);
	}
	if (CInput::GetKeyPress('X')) {
		XMVECTOR vec;
		XMMATRIX mtx;
		mtx = XMMatrixRotationY(m_RotationSpeed);
		vec = XMVector3TransformNormal(XMLoadFloat3(&m_Front), mtx);
		XMStoreFloat3(&m_Front, vec);
	}
	if (CInput::GetKeyPress('C')) {
		XMVECTOR vec;
		XMMATRIX mtx;
		mtx = XMMatrixRotationZ(m_RotationSpeed);
		vec = XMVector3TransformNormal(XMLoadFloat3(&m_Front), mtx);
		XMStoreFloat3(&m_Front, vec);
	}
	m_SpotLightDirection = XMFLOAT4(m_Front.x, m_Front.y, m_Front.z, 0);



	//XMVECTOR vec;
	//m_SpotLightDirection.x = cosf(x);
	//m_SpotLightDirection.y = cosf(y);
	//m_SpotLightDirection.z = cosf(z);
}
