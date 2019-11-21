//*****************************************************************************
// 定数バッファ
//*****************************************************************************

// マテリアルバッファ
cbuffer MaterialBuffer : register(b1)
{
    float4 Ambient;
    float4 Diffuse;
    float4 Specular;
    float4 Emission;
    float Shininess;
    float3 Dummy; //16bit境界用
}


struct PS_IN
{
    float4 inPosition : SV_POSITION;
    float4 inNormal : NORMAL0;
    float2 inTexCoord : TEXCOORD0;
    float4 inDiffuse : COLOR0;
};


//*****************************************************************************
// グローバル変数
//*****************************************************************************
Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);

//=============================================================================
// ピクセルシェーダ
//=============================================================================
float4 main(PS_IN input) : SV_Target
{
    float4 outDiffuse;
    outDiffuse = g_Texture.Sample(g_SamplerState, input.inTexCoord);

    outDiffuse *= input.inDiffuse;
    return outDiffuse;
}