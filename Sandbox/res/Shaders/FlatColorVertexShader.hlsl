
struct VS_INPUT
{
	float3 position : POSITION;
	float4 color : COLOR0;
};


struct PS_INPUT
{
	float4 position : SV_POSITION;
	float4 color : COLOR0;
};

PS_INPUT main(VS_INPUT vsin)
{
	PS_INPUT psin;
	psin.position = float4(vsin.position, 1.0f);
	psin.color = vsin.color;

	return psin;
}