#version 130
#ifdef GL_ES
	precision highp vec3;
	precision highp vec4;
	precision highp int;
	precision highp float;
#endif

varying vec3 normal;

void main()
{
	normal = gl_NormalMatrix * gl_Normal;
	gl_Position = ftransform();

}
