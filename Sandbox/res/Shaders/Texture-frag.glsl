#version 120

varying vec4 v_Color;
varying vec2 v_TextureCoord;

varying float v_TextureIdx;
varying float v_TillingFactor;

varying float v_Radius;
uniform sampler2D u_Textures[8];
uniform float u_time;

vec2 random2( vec2 p ) {
    return fract(sin(vec2(dot(p,vec2(127.1,311.7)),dot(p,vec2(269.5,183.3))))*43758.5453);
}

vec2 skew (vec2 st) {

    vec2 r = vec2(0.0);
    r.x = 1.1547*st.x;
    r.y = st.y+0.5*r.x;
    return r;
}

vec3 simplexGrid (vec2 st) {
    vec3 xyz = vec3(0.0);
    vec2 p = fract(skew(st));
    if (p.x > p.y) {
        xyz.xy = 1.0-vec2(p.x,p.y-p.x);
        xyz.z = p.y;
    } else {
        xyz.yz = 1.0-vec2(p.x-p.y,p.y);
        xyz.x = p.x;
    }
    return fract(xyz);
}

float circle(in vec2 _UV, in float _radius)
{
    vec2 dist = _UV - vec2(0.5f);

    return 1.-smoothstep(_radius - (_radius * 0.01f),
    _radius + (_radius * 0.01f),
    dot(dist, dist) * 4.0f);
}

void main()
{
    vec2 sim_st = v_TextureCoord;
    vec2 st = v_TextureCoord;
    st.x *= 10.0 / 10.0;


    st *= 10;
    sim_st *= 100;

    vec3 worleyColor = vec3(0.1, 0.64, 0.21);
    vec3 simColor = vec3(0.1, 0.64, 0.21);

    vec2 i_st = floor(st);
    vec2 f_st = fract(st);


    float m_dist = 1.25f;
    float z = 0.01;
    for(int y = -1; y <= 1; y++)
    {
        for(int x = -1; x <= 1; x++)
        {

            vec2 neighbor = vec2(float(x), float(y));
            vec3 point = vec3(random2(i_st + neighbor), z);
            //animation
            point.xy = 0.5 + 0.5*sin(u_time + 6.2831*point.xy);

            vec3 diff = vec3(neighbor, z) + point - vec3(f_st, z);
            float dist = length(diff);

            m_dist = min(m_dist, dist);
        }
    }


    worleyColor += m_dist;
    worleyColor += 1.-step(.02, m_dist);
    //draw grid
    //worleyColor.r += step(.98, f_st.x) + step(.98, f_st.y);
    simColor.rg = fract(skew(st));
    simColor = simplexGrid(sim_st);
    if (v_Radius == 1.0f)
    {
        gl_FragColor = texture2D(u_Textures[int(v_TextureIdx)], v_TextureCoord * v_TillingFactor) * circle(v_TextureCoord, v_Radius) *
        v_Color;
    } else {
        gl_FragColor = texture2D(u_Textures[int(v_TextureIdx)], v_TextureCoord * v_TillingFactor) * vec4(worleyColor, 1.0) *
        v_Color;
    }


}