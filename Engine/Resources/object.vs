#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 texCoord;

out vec3 FragPos;
out vec3 Normal;
out vec2 texcoord;

uniform mat4 TRS;
uniform mat4 view;
uniform mat4 proj;

void main()
{
    FragPos = vec3(TRS * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(TRS))) * aNormal;

    gl_Position = proj * view * vec4(FragPos, 1.0);

    texcoord = texCoord;
}
