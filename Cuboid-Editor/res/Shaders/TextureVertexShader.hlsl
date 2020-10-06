
cbuffer VERTEX_CONSTANT_BUFFER : register(b0)
{
    float4x4 projectionview;
}

struct VS_INPUT
{
    float3 Positions          : a_Position;
    float4 Color              : a_Color;
    float2 TextureCoordinates : a_TextureCoord;
    float1 TextureIdx         : a_TextureIdx;
    float1 TillingFactor      : a_TillingFactor;
    float1 PointSize          : a_PointSize;
    float1 Radius             : a_Radius;
};

struct PS_INPUT
{
    float4 Positions          : SV_POSITION;
    float4 Color              : a_Color;
    float2 TextureCoordinates : a_TextureCoord;
    uint TextureIdx         : a_TextureIdx;
    float TillingFactor      : a_TillingFactor;
    float PointSize          : a_PointSize;
    float Radius             : a_Radius;
};



PS_INPUT main(VS_INPUT vertex_input)
{
    PS_INPUT ps_output;
    
    
    ps_output.Positions             = mul(projectionview, float4(vertex_input.Positions, 1.0f));
    ps_output.Color                 = vertex_input.Color;
    ps_output.TextureCoordinates    = vertex_input.TextureCoordinates;
    ps_output.TextureIdx            = vertex_input.TextureIdx;
    ps_output.TillingFactor         = vertex_input.TillingFactor;
    ps_output.PointSize             = vertex_input.PointSize;
    ps_output.Radius                = vertex_input.Radius;
    
    
    
    return ps_output;
}