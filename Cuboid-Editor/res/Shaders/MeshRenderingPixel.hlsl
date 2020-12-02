
cbuffer Color
{
    float3 MeshColor;
    float3 LightDirection;
    float3 LightColor;
    float3 padding;
    
};

cbuffer Spot
{
    float4 color;
    float4 color1;
    float4 color2;
    float4 color3;
};

struct PS_INPUT
{
    float4 Positions : SV_POSITION;
    float2 TextureCoordinates : a_TextureCoord;
    float3 Normals : a_Normals;
};

float4 main(PS_INPUT ps_in) : SV_TARGET
{
    float3 normals = normalize(ps_in.Normals);
    float lightAmt = saturate(dot(normals, LightDirection));
    float3 fragLight = saturate(LightColor * lightAmt);
    
    float3 fragLightFinal = fragLight * MeshColor;
    
    return float4(fragLightFinal, 1.0f);
}