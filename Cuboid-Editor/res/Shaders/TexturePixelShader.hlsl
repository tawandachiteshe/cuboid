
struct PS_INPUT
{
    float4 Positions            : SV_POSITION;
    float4 Color                : a_Color;
    float2 TextureCoordinates   : a_TextureCoord;
    float TextureIdx           : a_TextureIdx;
    float TillingFactor        : a_TillingFactor;
    float PointSize            : a_PointSize;
    float Radius               : a_Radius;
};

SamplerState sampler0;
Texture2D textures[8] : register(t0);

float4 main(PS_INPUT ps_input) : SV_Target
{
    switch (asint(ps_input.TextureIdx))
    {
        case 0:
            return textures[0].Sample(sampler0, ps_input.TextureCoordinates) * ps_input.Color;
        case 1:
            return textures[1].Sample(sampler0, ps_input.TextureCoordinates) * ps_input.Color;
        case 2:
            return textures[2].Sample(sampler0, ps_input.TextureCoordinates) * ps_input.Color;
        case 3:
            return textures[3].Sample(sampler0, ps_input.TextureCoordinates) * ps_input.Color;
        case 4:
            return textures[4].Sample(sampler0, ps_input.TextureCoordinates) * ps_input.Color;
        case 5:
            return textures[5].Sample(sampler0, ps_input.TextureCoordinates) * ps_input.Color;
        case 6:
            return textures[6].Sample(sampler0, ps_input.TextureCoordinates) * ps_input.Color;
        case 7:
            return textures[7].Sample(sampler0, ps_input.TextureCoordinates) * ps_input.Color;
        default:
            return textures[0].Sample(sampler0, ps_input.TextureCoordinates) * ps_input.Color;
    }
 
    
    return textures[0].Sample(sampler0, ps_input.TextureCoordinates) * ps_input.Color;

}