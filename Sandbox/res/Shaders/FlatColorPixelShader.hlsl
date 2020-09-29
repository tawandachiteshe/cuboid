
struct PS_INPUT
{
	float4 position : SV_POSITION;
	float4 color : COLOR0;
    float2 uv : TEXCOORD0;
};

sampler sampler0;
Texture2D texture0;

float4 main(PS_INPUT psin) : SV_TARGET
{
    return texture0.Sample(sampler0, psin.uv);

}