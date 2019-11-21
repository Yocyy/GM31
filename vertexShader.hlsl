
//*****************************************************************************
// 定数バッファ
//*****************************************************************************

// マトリクスバッファ
cbuffer WorldBuffer : register(b0)
{
    matrix World;
}
cbuffer ViewBuffer : register(b1)
{
    matrix View;
}
cbuffer ProjectionBuffer : register(b2)
{
    matrix Projection;
}

// マテリアルバッファ
struct MATERIAL
{
    float4 Ambient;
    float4 Diffuse;
    float4 Specular;
    float4 Emission;
    float Shininess;
    float3 Dummy; //16bit境界用
};

cbuffer MaterialBuffer : register(b3)
{
    MATERIAL Material;
}


// ライトバッファ
struct LIGHT
{
    float4 Direction;
    float4 Diffuse;
    float4 Ambient;
};

cbuffer LightBuffer : register(b4)
{
    LIGHT Light;
}

struct VS_IN
{
    float4 inPosition : POSITION0;
    float4 inNormal : NORMAL0;
    float4 inDiffuse : COLOR0;
    float2 inTexCoord : TEXCOORD0;
    uint inInstanceID : SV_InstanceID;
};

struct VS_OUT
{
    float4 outPosition : SV_POSITION;
    float4 outNormal : NORMAL0;
    float2 outTexCoord : TEXCOORD0;
    float4 outDiffuse : COLOR0;
};

//=============================================================================
// 頂点シェーダ
//=============================================================================
VS_OUT main(VS_IN input)
{
    VS_OUT output;
    matrix wvp;

    input.inPosition.x += input.inInstanceID % 3;
    input.inPosition.z += input.inInstanceID / 3;

    wvp = mul(World, View);
    wvp = mul(wvp, Projection);

    output.outPosition = mul(input.inPosition, wvp);
    output.outNormal = input.inNormal;
    output.outTexCoord = input.inTexCoord;
	
    float4 worldNormal, normal;
    normal = float4(input.inNormal.xyz, 0.0);
    worldNormal = mul(normal, World);
    worldNormal = normalize(worldNormal);

    float light = 0.5 - 0.5 * dot(Light.Direction.xyz, worldNormal.xyz);

    output.outDiffuse = input.inDiffuse * Material.Diffuse * light * Light.Diffuse;
    output.outDiffuse += input.inDiffuse * Material.Ambient * Light.Ambient;
	//outDiffuse.a = 1.0;
          
    output.outDiffuse.a = input.inDiffuse.a + Material.Diffuse.a;

    return output;

}