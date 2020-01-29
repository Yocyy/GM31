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
    float4 Diffuse;
    float4 Ambient;
};

cbuffer LightBuffer : register(b1) //Shader.cppから転送される
{
    LIGHT Light;
}

struct VS_IN
{
    float4 inPosition : POSITION0;
    float4 inNormal : NORMAL0;
    float4 inBinormal : BINORMAL0;
    float4 inTangent : TANGENT0;
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
    float4 outBinormal : BINORMAL0;
    float4 outTangent : TANGENT0;
};

VS_OUT main(in VS_IN input)
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
    
    input.inBinormal.w = 0.0f;
    output.outBinormal = mul(input.inBinormal, World);
    
    input.inTangent.w = 0.0f;
    output.outTangent = mul(input.inTangent, World);
    
    return output; //戻り値
}