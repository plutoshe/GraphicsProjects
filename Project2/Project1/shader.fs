#version 330 core //告诉编译器我们的目标GLSL编译器版本是3.3
//uniform vec4 inputColor;
out vec4 FragColor;  // 片段着色器的输出颜色变量
uniform vec4 inputColor;
// 着色器的唯一入口函数
void main()
{
    // 定义输出颜色值
    FragColor = inputColor;
} 