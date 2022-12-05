#version 330 core

struct Material
{
	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 specularColor;
	float shininess;
};

uniform Material material;
uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec3 eyePosition;

in vec3 v_Position;
in vec3 v_normal;




void main()
{
	float ambientStrength = 0.1;
	vec3 ambient = material.ambientColor * lightColor;

	vec3 normal = normalize(v_normal);
	vec3 lightDir = normalize(lightPosition - v_Position);
	float diffuseStrength = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = material.diffuseColor * diffuseStrength * lightColor;

	vec3 view = normalize(eyePosition - v_Position);

	vec3 relectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(view, relectDir), 0.0), material.shininess);
	vec3 specular = spec * material.specularColor * lightColor;
	gl_FragColor = vec4(ambient + diffuse + specular, 1.0);
}