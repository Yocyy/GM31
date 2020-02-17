SamplerState g_Sampler : register(s10);
Texture2D g_Texture[6] : register(t10);
Texture2D g_Tex : register(t0);

cbuffer ConstantBuffer : register(b0) //Shader.cpp‚©‚ç“]‘—‚³‚ê‚é
{
    matrix World;
    matrix View;
    matrix Projection;
    float4 CameraPosition;
}
struct PS_IN
{
    float4 inPosition : SV_POSITION;
    float2 inTexCoord : TEXCOORD0;
    float4 inNormal : NORMAL0;
};

float4 main(in PS_IN input) : SV_Target
{ 
    float4 color = {1,1,1,1 };
    if (input.inNormal.z == -1)
        color = g_Texture[0].Sample(g_Sampler, input.inTexCoord);
    if (input.inNormal.z == 1)
        color = g_Texture[2].Sample(g_Sampler, input.inTexCoord);
    
    if (input.inNormal.x == -1)
        color = g_Texture[1].Sample(g_Sampler, input.inTexCoord);
    
    if (input.inNormal.x == 1)
        color = g_Texture[3].Sample(g_Sampler, input.inTexCoord);
    
    if (input.inNormal.y == -1)
        color = g_Texture[5].Sample(g_Sampler, input.inTexCoord);
    
    if (input.inNormal.y == 1)
        color = g_Texture[4].Sample(g_Sampler, input.inTexCoord);
    
    return color;
}