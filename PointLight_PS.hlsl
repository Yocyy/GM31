struct PS_IN
{
    float4 pos : SV_POSITION;
    float4 posw : POSITION0;
    float4 norw : NORMAL0;
};
 
cbuffer ConstantBuffer
{
    float4x4 World; //[hΟ·sρ
    float4x4 View; //r[Ο·sρ
    float4x4 Projection; //§ΛeΟ·sρ
    float4 Light; //υΉΐW
    float4 Attenuation; //υΉΈp[^
}

float4 ps_main(PS_IN input)
{
    float3 dir;
    float len;
    float colD;
    float colA;
    float col;
         
    //_υΉΜϋό
    dir = Light.xyz - input.posw.xyz;
 
    //_υΉΜ£
    len = length(dir);
 
    //_υΉΜϋόπnormalize
    dir = dir / len;
 
    //gU
    colD = saturate(dot(normalize(input.norw.xyz), dir));
    //Έ
    colA = saturate(1.0f / (Attenuation.x + Attenuation.y * len + Attenuation.z * len * len));
 
    col = colD * colA;
    return float4(col, col, col, 1.0f);
}