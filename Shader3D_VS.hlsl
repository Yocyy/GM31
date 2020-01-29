#define LIGHT_NUM 4

cbuffer ConstantBuffer : register(b0) //Shader.cppから転送される
{
    matrix World;
    matrix View;
    matrix Projection;
    float4 CameraPosition;
}

struct LIGHT
{
    float4 Direction;
    float4 Position;
    float4 Color;
    float Pow;
    float Attenuation0;
    float Attenuation1;
    float Attenuation2;
    uint type;
    float3 Dummy;
};

cbuffer LightBuffer : register(b2) //LightManagaer.cppから転送される
{
    LIGHT Light[LIGHT_NUM];
}

struct VS_IN
{
    float4 inPosition : POSITION0;
    float4 inNormal : NORMAL0;
    float4 inDiffuse : COLOR0;
    float2 inTexCoord : TEXCOORD0;
};

struct VS_OUT
{
    float4 outPosition : SV_POSITION;
    float4 outDiffuse : COLOR0;
    float2 outTexCoord : TEXCOORD0;
    float4 outSpecular : COROL1;
    float4 outWorldPosition : POSITION1;
    float4 outNormal : NORMAL0;
    float3 outLightDirection : POSITION2;
};

VS_OUT vs_main(in VS_IN input)
{
    VS_OUT output;
    
    matrix wvp;
    wvp = mul(World, View); //マトリクス
    wvp = mul(wvp, Projection); //マトリクス乗算

    output.outWorldPosition = mul(input.inPosition, World);
    input.inNormal.w = 0.0f;
    output.outNormal = mul(input.inNormal, World);
    output.outDiffuse = input.inDiffuse;
    output.outTexCoord = input.inTexCoord;
    
    output.outPosition = mul(input.inPosition, wvp); //座標変換
    
    output.outLightDirection = output.outWorldPosition - Light[3].Position;
    
    return output; //戻り値
}