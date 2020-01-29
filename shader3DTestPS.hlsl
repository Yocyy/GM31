//*****************************************************************************
// グローバル変数
//*****************************************************************************
Texture2D g_Texture : register(t0);
//Texture2D g_Texture[2] : register(t0);
SamplerState g_SamplerState : register(s0);

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

struct PS_IN
{
    float4 inPosition : SV_POSITION;
    float4 inDiffuse : COLOR0;
    float2 inTexCoord : TEXCOORD0;
    float4 inSpecular : COROL1;
    float4 inWorldPosition : POSITION1;
    float4 inNormal : NORMAL0;
};

float4 main(in PS_IN input) : SV_Target
{
    float4 outDiffuse;
    outDiffuse = g_Texture.Sample(g_SamplerState, input.inTexCoord); //画像のリソースから画像を表示
    
        
    if (outDiffuse.a <= 0.0f)
    {
        discard;
    }
    
    outDiffuse *= Light.Ambient * 1.0;  //アンビエントライト、色×色の強さ(0.0～1.0)
    
    //ピクセルライティング
    input.inNormal = normalize(input.inNormal);
    float light = 0.5 - dot(input.inNormal.xyz, Light.Direction.xyz) * 0.5; //真上から光がきたと仮定する(長さは１)
    light = saturate(light); //0以下を0に、1以上を1にする関数
    outDiffuse *= light;
    outDiffuse.a = 1.0;
    
    outDiffuse += Light.Diffuse * 1.0;  //ライトディフューズ、色×色の強さ(0.0～1.0)

    //スペキュラー設定
    float3 refv = reflect(Light.Direction.xyz, input.inNormal.xyz); //反射ベクトルを求める    １、反射させる光　２、反射する法線
    refv = normalize(refv); //正規化
    float3 eyev = input.inWorldPosition - CameraPosition; //視線ベクトル    カメラから面の頂点までのベクトル
    eyev = normalize(eyev); //正規化
    
    float specular = -dot(eyev, refv);
    specular = saturate(specular);
    specular = pow(specular, 20); //10乗   大きくすると強くなり、小さくすると弱くなる
    outDiffuse += specular;
    
    return outDiffuse;
}