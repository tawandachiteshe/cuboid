#version 120

varying vec4 v_Color;
varying vec2 v_TextureCoord;

varying float v_TextureIdx;
varying float v_TillingFactor;

varying float v_Radius;
uniform sampler2D u_Textures[8];

float circle(in vec2 _UV, in float _radius)
{
    vec2 dist = _UV - vec2(0.5f);

    return 1.-smoothstep(_radius - (_radius * 0.01f),
                         _radius + (_radius * 0.01f),
                         dot(dist,dist) * 4.0f);
}

void main()
{
        if(v_Radius == 1.0f)
        {
            gl_FragColor = texture2D(u_Textures[int(v_TextureIdx)], v_TextureCoord * v_TillingFactor) * circle(v_TextureCoord, v_Radius) *
                           v_Color;
        } else{
            gl_FragColor = texture2D(u_Textures[int(v_TextureIdx)], v_TextureCoord * v_TillingFactor) *
                           v_Color;
        }


}