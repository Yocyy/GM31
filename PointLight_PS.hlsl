struct PS_IN
{
    float4 pos : SV_POSITION;
    float4 posw : POSITION0;
    float4 norw : NORMAL0;
};
 
cbuffer ConstantBuffer
{
    float4x4 World; //���[���h�ϊ��s��
    float4x4 View; //�r���[�ϊ��s��
    float4x4 Projection; //�����ˉe�ϊ��s��
    float4 Light; //�������W
    float4 Attenuation; //���������p�����[�^
}

float4 ps_main(PS_IN input)
{
    float3 dir;
    float len;
    float colD;
    float colA;
    float col;
         
    //�_�����̕���
    dir = Light.xyz - input.posw.xyz;
 
    //�_�����̋���
    len = length(dir);
 
    //�_�����̕�����normalize
    dir = dir / len;
 
    //�g�U
    colD = saturate(dot(normalize(input.norw.xyz), dir));
    //����
    colA = saturate(1.0f / (Attenuation.x + Attenuation.y * len + Attenuation.z * len * len));
 
    col = colD * colA;
    return float4(col, col, col, 1.0f);
}