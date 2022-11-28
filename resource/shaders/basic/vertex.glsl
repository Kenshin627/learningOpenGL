#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 uv;
out vec2 v_Uv;
void main()
{
	v_Uv = uv;
	gl_Position = position;
}
