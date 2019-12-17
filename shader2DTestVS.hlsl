cbuffer ConstantBuffer : register(b0)
{
    matrix World;
    matrix View;
    matrix Projection;
}

struct VS_IN
{
    float4 inPosition : POSITION0;
    float4 inDiffuse : COLOR0;
    float2 inTexCoord : TEXCOORD0;
};


struct VS_OUT
{
    float4 outPosition : SV_POSITION;
    float4 outDiffuse : COLOR0;
    float2 outTexCoord : TEXCOORD0;
};

void main(in VS_IN input,out VS_OUT output) 
{
    output.outDiffuse = input.inDiffuse;
    output.outPosition = mul(input.inPosition, Projection);
    output.outTexCoord = input.inTexCoord;
}