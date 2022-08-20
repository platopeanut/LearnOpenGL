#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    // Normal = aNormal;
    // 对法向量也进行model变换
    // 注意！如果model对物体进行了不等比缩放操作，法向量需要使用Normal Matrix进行变换
    // Normal Matrix变换操作如下（注意，矩阵求逆非常耗时！）
    // Normal = mat3(transpose(inverse(model))) * aNormal;
    Normal = vec3(model * vec4(aNormal, 1.0));


    gl_Position = projection * view * vec4(FragPos, 1.0);
}