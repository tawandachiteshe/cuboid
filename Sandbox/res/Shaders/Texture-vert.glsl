#version 120

attribute vec4 a_Color;
attribute float a_PointSize;

attribute float a_Radius;

attribute vec3 a_Position;
attribute vec2 a_TextureCoord;

attribute float a_TextureIdx;
attribute float a_TillingFactor;

varying vec4 v_Color;
varying vec2 v_TextureCoord;

varying float v_TextureIdx;
varying float v_TillingFactor;

varying float v_Radius;

uniform mat4 u_ProjectionViewMatrix;


void main()
{
    v_Color = a_Color;
    v_TextureCoord = a_TextureCoord;

    v_TextureIdx = a_TextureIdx;
    v_TillingFactor = a_TillingFactor;

    v_Radius = a_Radius;

    gl_Position = u_ProjectionViewMatrix * vec4(a_Position, 1.0f);
    gl_PointSize = a_PointSize;
}