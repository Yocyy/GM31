cbuffer ConstantBuffer : register(b0) //Shader.cppから転送される
{
    matrix World;
    matrix View;
    matrix Projection;
    float4 CameraPosition;
}

struct VS_IN
{
    float4 inPosition : POSITION0;
    float4 inNormal : NORMAL0;
    float2 inTexCoord : TEXCOORD0;
};

struct VS_OUT
{
    float4 outPosition : SV_POSITION;
    float2 outTexCoord : TEXCOORD0;
 //   float4 outWorldPosition : POSITION1;
    float4 outNormal : NORMAL0;
};

VS_OUT main(in VS_IN input)
{
    VS_OUT output;
    
    matrix wvp;
    wvp = mul(World, View); //マトリクス
    wvp = mul(wvp, Projection); //マトリクス乗算

    input.inNormal.w = 0.0f;
 //   output.outWorldPosition = mul(input.inPosition, World);
    output.outNormal = input.inNormal;
    output.outTexCoord = input.inTexCoord;
    
    output.outPosition = mul(input.inPosition, wvp); //座標変換
    
    return output; //戻り値
}