cbuffer ConstantBuffer : register(b0)
{
    float4x4 World; //���[���h�ϊ��s��
    float4x4 View; //�r���[�ϊ��s��
    float4x4 Projection; //�����ˉe�ϊ��s��
    float4 Light;
    float4 Attenuation;
}

struct VS_IN
{
    float4 pos : POSITION0;
    float4 nor : NORMAL0;
};

struct VS_OUT
{
    float4 pos : SV_POSITION;
    float4 posw : POSITION0;
    float4 norw : NORMAL0;
};

VS_OUT vs_main(VS_IN input)
{
    
    VS_OUT output;
    float3 nor;
    float col;
 
    output.posw = mul(input.pos, World);
    output.pos = mul(output.posw, View);
    output.pos = mul(output.pos, Projection);
         
    output.norw = mul(input.nor, World);
 
    return output;
}