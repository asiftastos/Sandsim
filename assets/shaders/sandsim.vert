#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;

uniform mat4 proj;

layout (location = 0) out vec4 color;

out gl_PerVertex
{
    vec4 gl_Position;
};

void main()
{
    color = vec4(aCol, 1.0);
    gl_Position = proj * vec4(aPos, 1.0);
}
