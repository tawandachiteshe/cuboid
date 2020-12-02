
cbuffer VERTEX_CONSTANT_BUFFER1 : register(b0)
{
    float4x4 projectionview2;
};

cbuffer VERTEX_CONSTANT_BUFFER2 : register(b1)
{
    float4x4 transform;
    float4x4 projectionview;
    float4x4 inverseTransposeTransform;
}

struct VS_INPUT
{
    float3 Positions : a_Position;
    float2 TextureCoordinates : a_TextureCoord;
    float3 Normals : a_Normals;

};

struct PS_INPUT
{
    float4 Positions : SV_POSITION;
    float2 TextureCoordinates : a_TextureCoord;
    float3 Normals : a_Normals;
};

PS_INPUT main(VS_INPUT vs_in)
{
    
    PS_INPUT ps_out;
    
    ps_out.Positions = mul(projectionview, mul(transform, float4(vs_in.Positions, 1)));
    ps_out.TextureCoordinates = vs_in.TextureCoordinates;
    ps_out.Normals = mul(inverseTransposeTransform, float4(vs_in.Normals, 1.0f)).xyz;
    
    return ps_out;
}
