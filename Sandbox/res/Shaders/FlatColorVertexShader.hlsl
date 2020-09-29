
cbuffer vertexBuffer : register(b0)
{
	float4x4 ProjectionMatrix;
};

struct VS_INPUT
{
	float3 position : POSITION;
	float4 color : COLOR0;
    float2 uv : TEXCOORD0;
};


struct PS_INPUT
{
	float4 position : SV_POSITION;
	float4 color : COLOR0;
    float2 uv : TEXCOORD0;
};

PS_INPUT main(VS_INPUT vsin)
{
	PS_INPUT psin;
	psin.position = mul(ProjectionMatrix, float4(vsin.position, 1.0f));
	psin.color = vsin.color;
    psin.uv = vsin.uv;
	
	return psin;
}