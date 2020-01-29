#pragma once


struct CONSTANT
{
	XMFLOAT4X4 WorldMatrix;
	XMFLOAT4X4 ViewMatrix;
	XMFLOAT4X4 ProjectionMatrix;
	XMFLOAT4	CameraPosition;
};

enum class VS_CSO
{
	MIN = -1,
	Shader_2D,
	Shader_3D,
	NormalMapping,
	MAX,
};

enum class PS_CSO
{
	MIN = -1,
	Shader_2D,
	Shader_3D,
	NormalMapping,
	MAX,
};

class CShader
{
private:
	const char* VSshaderfile[static_cast<unsigned int>(VS_CSO::MAX)] = {
		"x64/debug/shader2DTestVS.cso",
		"x64/debug/Shader3D_VS.cso",
		"x64/debug/Shader3DNormalMappingVS.cso"
	};
	const char* PSshaderfile[static_cast<unsigned int>(PS_CSO::MAX)] = {
		"x64/debug/shader2DTestPS.cso",
		"x64/debug/Shader3D_PS.cso",
		"x64/debug/Shader3DNormalMappingPS.cso"
	};

	ID3D11VertexShader*     m_VertexShader;
	ID3D11PixelShader*      m_PixelShader;
	ID3D11InputLayout*      m_VertexLayout;

	//ID3D11Buffer*			m_WorldBuffer;
	//ID3D11Buffer*			m_ViewBuffer;
	//ID3D11Buffer*			m_ProjectionBuffer;
	ID3D11Buffer*			m_ConstantBuffer;
	ID3D11Buffer*			m_MaterialBuffer;
	ID3D11Buffer*			m_LightBuffer;
	ID3D11Buffer*			m_VertexBuffer;
	ID3D11Buffer*			m_IndexBuffer;

	CStbTexture*				m_Texture;
	CONSTANT				m_Constant;
	LIGHT					m_Light;
	MATERIAL				m_Material;

public:



	void Init(const VS_CSO VSIndex, const PS_CSO PSIndex);

	void Uninit();
	void Set();

	void SetWorldMatrix(XMFLOAT4X4* WorldMatrix) { m_Constant.WorldMatrix = Transpose(WorldMatrix); };
	void SetViewMatrix(XMFLOAT4X4* ViewMatrix) { m_Constant.ViewMatrix = Transpose(ViewMatrix); };
	void SetProjectionMatrix(XMFLOAT4X4* ProjectionMatrix) { m_Constant.ProjectionMatrix = Transpose(ProjectionMatrix); };
	void SetCameraPosition(XMFLOAT4* CameraPosition) { m_Constant.CameraPosition = *CameraPosition; };
	void SetLight(LIGHT light) { m_Light = light; };
	void SetMaterial(MATERIAL Material) { m_Material = Material; };

	void SetVertexBuffers(ID3D11Buffer* VertexBuffer) { m_VertexBuffer = VertexBuffer; };
	void SetIndexBuffer(ID3D11Buffer* IndexBuffer) { m_IndexBuffer = IndexBuffer; };
	void SetTexture(CStbTexture* Texture) { m_Texture = Texture; };

	XMFLOAT4X4 Transpose(XMFLOAT4X4* Matrix)
	{
		XMFLOAT4X4 outMatrix;

		outMatrix._11 = Matrix->_11;
		outMatrix._12 = Matrix->_21;
		outMatrix._13 = Matrix->_31;
		outMatrix._14 = Matrix->_41;

		outMatrix._21 = Matrix->_12;
		outMatrix._22 = Matrix->_22;
		outMatrix._23 = Matrix->_32;
		outMatrix._24 = Matrix->_42;

		outMatrix._31 = Matrix->_13;
		outMatrix._32 = Matrix->_23;
		outMatrix._33 = Matrix->_33;
		outMatrix._34 = Matrix->_43;

		outMatrix._41 = Matrix->_14;
		outMatrix._42 = Matrix->_24;
		outMatrix._43 = Matrix->_34;
		outMatrix._44 = Matrix->_44;

		return outMatrix;
	}

};