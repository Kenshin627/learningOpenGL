#version 330 core

precision highp float;
layout(location = 0) out vec4 color;
in vec3 v_Color;
uniform vec4 u_Color;

void main()
{
	color = vec4(v_Color, 1.0);
}