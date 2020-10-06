
cbuffer vertexBuffer : register(b0)
{
	float4x4 ProjectionMatrix;
};

struct VS_INPUT
{
	float3 position : a_Position;
	float4 color : a_Color;
    float2 uv : a_Texcoord;
    int idx : a_textureidx;
};


struct PS_INPUT
{
	float4 position : SV_POSITION;
    float4 color : a_Color;
    float2 uv : a_Texcoord;
    int idx : a_textureidx;
};

PS_INPUT main(VS_INPUT vsin)
{
	PS_INPUT psin;
	psin.position = mul(ProjectionMatrix, float4(vsin.position, 1.0f));
	psin.color = vsin.color;
    psin.uv = vsin.uv;
    psin.idx = vsin.idx;
	
	return psin;
}