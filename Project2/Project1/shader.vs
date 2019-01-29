﻿#version 330  //告诉编译器我们的目标GLSL编译器版本是3.3

layout (location = 0) in vec3 Position; // 绑定定点属性名和属性，方式二缓冲属性和shader属性对应映射
//layout (location = 1) uniform vec4 test;
//uniform float myVar;

float xLowBound = -100.f;
float xUpperBound = 100.f;
float yLowBound = -100.f;
float yUpperBound = 100.f;
float zLowBound = 10.f;
float zUpperBound = 20.f;

void main()
{
     vec4 trans = vec4(test.x, Position.y, Position.z, Position.z) ;
    mat4 aMat4 = mat4(2 * zLowBound / (xUpperBound - xLowBound), 0.0, 0.0, 0.0,  // 1. column
                  0.0, 2 * zLowBound / (yUpperBound - yLowBound), 0.0, 0.0,  // 2. column
                  (xUpperBound + xLowBound) / (xUpperBound - xLowBound),(yLowBound + yUpperBound) / (yUpperBound - yLowBound), -(zLowBound + zUpperBound)/ (zUpperBound - zLowBound), 0.0,  // 3. column
                  0.0, 0.0, 0.0, 2 * zUpperBound * zLowBound / (zUpperBound - zLowBound));

        //
       // 0,,0,0,
        //,0,
        //0,0,0,,
   // vec3 tile=texture2D(colMap, coords.st).xyz;
   // vec4 col = vec4(tile, 1.0);
   //      if (test.x > 1) {
   //         col.x+=1;
   //      }
     vec4 trans1 = aMat4 * vec4(1.0, 1.0, 1.0, 1.0);
    gl_Position =   trans * aMat4;
    //gl_FragColor = col;
 //gl_Position = vec4(0.1 * Position.x, 0.1 * Position.y, Position.z, 1.0); // 为glVertexAttributePointer提供返回值
}