#version 330 core

precision highp float;
layout(location = 0) out vec4 color;
in vec2 v_Uv;
uniform sampler2D sampler;

void main()
{
	vec4 textureColor = texture(sampler, v_Uv);
	color = textureColor;
}