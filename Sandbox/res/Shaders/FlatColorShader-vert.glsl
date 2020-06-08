uniform mat4 u_ProjectionViewMatrix;

attribute vec4 a_Color;
attribute vec3 a_Position;
attribute vec2 a_TextureCoord;


varying vec4 v_Color;
varying vec2 v_TextureCoord;
void main()
{
	v_Color = a_Color;
	v_TextureCoord = a_TextureCoord;

	gl_Position = u_ProjectionViewMatrix * vec4(a_Position, 1.0f);
}