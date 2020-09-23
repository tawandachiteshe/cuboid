
struct PS_INPUT
{
	float4 position : SV_POSITION;
	float4 color : COLOR0;
};

float4 main(PS_INPUT psin) : SV_TARGET
{
	return psin.color;
}