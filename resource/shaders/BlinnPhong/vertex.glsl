#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;

out vec3 v_Position;
out vec3 v_Normal;

uniform mat4 u_Mvp;
uniform mat4 u_Model;
uniform mat3 u_itModel;

void main()
{
	v_Normal = u_itModel * normal;
	v_Position = vec3(u_Model * position);
	gl_Position = u_Mvp * position;
}