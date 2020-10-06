
struct PS_INPUT
{
	float4 position : SV_POSITION;
	float4 color : a_Color;
    float2 uv : a_Texcoord;
    int idx : a_textureidx;
};

sampler sampler0;
Texture2D texture0;

float4 main(PS_INPUT psin) : SV_TARGET
{
    uint idx = 0;
    
   
    return texture0.Sample(sampler0, psin.uv) * float4(1.0f, 0.0f, 0.0f, 1.0f);

}