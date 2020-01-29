#define LIGHT_DIRECTION  0
#define LIGHT_POINTLIGHT 1
#define LIGHT_SPOTLIGHT  2

#define LIGHT_NUM 4

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

struct MATERIAL
{
    float4 Ambient;
    float4 Diffuse;
    float4 SpecularColor;
    float4 Emission;
    float Shininess;
    float3 Dummy; //16bit境界用
};

cbuffer MaterialBuffer : register(b1) //Shader.cppから転送される
{
    MATERIAL Material;
}

struct LIGHT
{
    float4 Direction;
    float4 Position;
    float4 Color;
    float  Pow;
    float  Attenuation0;
    float  Attenuation1;
    float  Attenuation2;
    uint   type;
    float3 Dummy;
};

cbuffer LightBuffer : register(b2) //LightManagaer.cppから転送される
{
    LIGHT Light[LIGHT_NUM];
}


struct PS_IN
{
    float4 inPosition : SV_POSITION;
    float4 inDiffuse : COLOR0;
    float2 inTexCoord : TEXCOORD0;
    float4 inSpecular : COROL1;
    float4 inWorldPosition : POSITION1;
    float4 inNormal : NORMAL0;
    float3 inLightDirection : POSITION2;
};
 
float4 DoLight(PS_IN input, LIGHT light, float4 sampleColor);
float4 DirectionalLight(PS_IN input, LIGHT light, float4 sampleColor);
float4 PointLight(PS_IN input, LIGHT light, float4 sampleColor);
float4 SpotLight(PS_IN input, LIGHT light, float4 sampleColor);

float4 ps_main(PS_IN input) : SV_Target
{
    float4 outDiffuse = 0;
    
    float4 sampleColor = g_Texture.Sample(g_SamplerState, input.inTexCoord); //画像のリソースから画像を表示
    if (sampleColor.a <= 0.0f)
    {
        discard;
    }
    
    for (int i = 0; i < LIGHT_NUM;i++)
        outDiffuse += saturate(DoLight(input, Light[i], sampleColor));
    
    
    //outDiffuse = saturate(DoLight(input, Light[3], sampleColor));
    return outDiffuse;
}

float4 DoLight(PS_IN input, LIGHT light,float4 sampleColor)
{
    
    switch (light.type)
    {
        case LIGHT_DIRECTION:
            return DirectionalLight(input, light, sampleColor);
            break;
        case LIGHT_POINTLIGHT:
            return PointLight(input, light, sampleColor);
            break;
        case LIGHT_SPOTLIGHT:
            return SpotLight(input, light, sampleColor);
            break;
        default:
            break;
    }
    return float4(0, 0, 0, 0);
}

float4 DirectionalLight(PS_IN input, LIGHT Light1, float4 sampleColor)
{
    float4 outDiffuse;
    outDiffuse = sampleColor;

   // outDiffuse *= Material.Ambient * 1.0; //アンビエントライト、色×色の強さ(0.0～1.0)
    outDiffuse *= saturate(Material.Ambient * 0.3 + Material.Diffuse * (Light1.Color * Light1.Pow));
    //outDiffuse += Material.Diffuse * Light.Color * Light.Pow;
    
    //ピクセルライティング
    input.inNormal = normalize(input.inNormal);
    float light = 0.5 - dot(input.inNormal.xyz, Light1.Direction.xyz) * 0.5; //真上から光がきたと仮定する(長さは１)
    light = saturate(light); //0以下を0に、1以上を1にする関数
    
    //outDiffuse += Light.Color * 1.0; //ライトディフューズ、色×色の強さ(0.0～1.0)

    //スペキュラー設定
    float3 refv = reflect(Light1.Direction.xyz, input.inNormal.xyz); //反射ベクトルを求める    １、反射させる光　２、反射する法線
    refv = normalize(refv); //正規化
    float3 eyev = input.inWorldPosition - CameraPosition; //視線ベクトル    カメラから面の頂点までのベクトル
    eyev = normalize(eyev); //正規化
    
    float specular = -dot(eyev, refv);
    specular = saturate(specular);
    specular = pow(specular, Material.Shininess); //10乗   大きくすると強くなり、小さくすると弱くなる
    //outDiffuse += specular;
    light = (light + specular);
    outDiffuse *= light *  Light1.Pow;
    //outDiffuse += specular * Material.SpecularColor * Light1.Color;
    outDiffuse.a = 1.0;
    return outDiffuse;
    
}

float4 PointLight(PS_IN input, LIGHT Light1, float4 sampleColor)
{
    float4 outDiffuse;
    outDiffuse = sampleColor;
    outDiffuse *= saturate(Material.Ambient * 0.3 + Material.Diffuse * (Light1.Color * Light1.Pow)); //アンビエントライト、色×色の強さ(0.0～1.0)
    
    //ピクセルライティング
    input.inNormal = normalize(input.inNormal);
    float3 direction = normalize(Light1.Position.xyz - input.inWorldPosition.xyz);
    float light = max(dot(input.inNormal.xyz, direction), 0); //真上から光がきたと仮定する(長さは１)
    
    //ピクセルからライトの距離
    float distanceLight = distance(Light1.Position.xyz, input.inWorldPosition.xyz);
    //減衰率
    float col = 1 / (Light1.Attenuation0 + Light1.Attenuation1 * distanceLight + Light1.Attenuation2 * (distanceLight * distanceLight));

    //スペキュラー設定
    float3 refv = reflect(direction, input.inNormal.xyz); //反射ベクトルを求める    １、反射させる光　２、反射する法線
    refv = normalize(refv); //正規化
    float3 eyev = CameraPosition - input.inWorldPosition; //視線ベクトル    カメラから面の頂点までのベクトル
    eyev = normalize(eyev); //正規化
    
    float specular = -dot(eyev, refv);
    specular = saturate(specular);
    specular = pow(specular, Material.Shininess); //10乗   大きくすると強くなり、小さくすると弱くなる
    light = (light + specular) * col;
    outDiffuse *= light * Light1.Pow; //ライトディフューズ、色×色の強さ(0.0～1.0)
    //outDiffuse += specular * Material.SpecularColor * Light1.Color * col;
    outDiffuse.a = 1.0;
    
    return outDiffuse;
}



float4 SpotLight(PS_IN input, LIGHT Light, float4 sampleColor)
{
    float4 outDiffuse = sampleColor;
   // float3 LightDirection = input.inLightDirection;
    float4 color = Light.Color;
    //float ambient = 0.1;
    float LightCos = -0;
    float LightDecay = 2.0;
    float LightStrength = 3;
    float3 ldir = normalize(input.inLightDirection);
    float shade = 0;
    float coneFactor = dot(ldir, normalize(Light.Direction.xyz)); //< スポットライトの範囲内かどうか
    
    if (coneFactor > LightCos)
    {
        shade = dot(normalize(input.inNormal.xyz), -ldir) * coneFactor * Light.Pow; //< 減衰とライトの強さを考慮
        outDiffuse *= color * shade;
    }
    else
    {
        outDiffuse = 0;
    }
        //ピクセルからライトの距離
    float distanceLight = distance(Light.Position.xyz, input.inWorldPosition.xyz);
    //減衰率
    float col = 1 / (Light.Attenuation0 + Light.Attenuation1 * distanceLight + Light.Attenuation2 * (distanceLight * distanceLight));
    
    outDiffuse *= col;
    //outDiffuse.a = 1.0;
    
    return outDiffuse;
}