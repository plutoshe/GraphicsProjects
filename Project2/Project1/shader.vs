#version 330

layout (location = 0) in vec3 Position;

// WVP标准
uniform mat4 gWorld;
float xLowBound = -0.57f;
float xUpperBound = 0.57f;
float yLowBound = -0.57f;
float yUpperBound = 0.57f;
float zLowBound = 1.f;
float zUpperBound = 2.f;
out vec4 Color;

void main()
{
    vec4 trans = vec4(Position, 1.0);
    mat4 aMat4 = mat4(
        2 * zLowBound / (xUpperBound - xLowBound), 0.0, 0.0, 0.0,  // column
        0.0, 2 * zLowBound / (yUpperBound - yLowBound), 0.0, 0.0,  
        (xUpperBound + xLowBound) / (xUpperBound - xLowBound),(yLowBound + yUpperBound) / (yUpperBound - yLowBound), -(zLowBound + zUpperBound)/ (zUpperBound - zLowBound), -1,  // 3. column
        0.0, 0.0, 0.0, -2 * zUpperBound * zLowBound / (zUpperBound - zLowBound));

    // calculate the new vertex
    gl_Position = aMat4 * trans;
    gl_Position = gl_Position / -gl_Position.w;    
    gl_Position.w = 1;


    //gWVP * 
    //gl_Position = 
    float a = clamp((Position.z - zLowBound) / (zUpperBound - zLowBound), 0.f, 1.f);
    Color = vec4(a, a, 1, 1);
}
// #version 330 core

// layout (location = 0) in vec3 Position; 

// float xLowBound = -1024.f;
// float xUpperBound = 1024.f;
// float yLowBound = -800.f;
// float yUpperBound = 800.f;
// float zLowBound = -200.f;
// float zUpperBound = 200.f;
// uniform vec3 viewport_pos;
// uniform vec4 viewport_rot;

// vec4 QuaternionMultiply(vec4 p, vec4 q) {
// 	return vec4(
// 			p.w * q.x + p.x * q.w + p.y * q.z - p.x * q.y,
// 			p.w * q.y - p.x * q.z + p.y * q.w + p.z * q.x,
// 			p.w * q.z + p.x * q.y - p.y * q.x + p.z * q.w,
// 			-p.x * q.x - p.y * q.y - p.z * q.z + p.w * q.w);
// }
// vec4 getConjugate(vec4 p)
// {
// 	return vec4(-p.x, -p.y, -p.z, p.w);
// }

// float length(vec4 p) {
//     return sqrt(p.x * p.x + p.y * p.y + p.z * p.z + p.w * p.w);
// }

// vec4 normalized(vec4 p) {
//     float len = length(p);
//     if (len > 0)
//         return p / len; 
//     return p;
// } 

// void main()
// {
//     // calculate the coordinate based on this origin
//     vec4 qua = vec4(
//         Position.x - viewport_pos.x, 
//         Position.y - viewport_pos.y,
//         Position.z - viewport_pos.z,
//         0);
//     float mag = length(qua);
//     qua = normalized(qua);
//     qua = QuaternionMultiply(QuaternionMultiply(viewport_rot, qua), getConjugate(viewport_rot));
//     qua = normalized(qua) * mag;
    
//     vec4 trans = vec4(
//         qua.x ,
//         qua.y , 
//         qua.z,
//         qua.z); 
    
//     // rotate vertex based on current axis


    
//     // vec4 trans = vec4(
//     //     trans.x,
//     //     trans.y, 
//     //     trans.z, 
//     //     trans.z) ;

//     // calculate the clip space tranformation matrix
    
//     mat4 aMat4 = mat4(
//         2 * zLowBound / (xUpperBound - xLowBound), 0.0, 0.0, 0.0,  // column
//         0.0, 2 * zLowBound / (yUpperBound - yLowBound), 0.0, 0.0,  
//         (xUpperBound + xLowBound) / (xUpperBound - xLowBound),(yLowBound + yUpperBound) / (yUpperBound - yLowBound), -(zLowBound + zUpperBound)/ (zUpperBound - zLowBound), -1,  // 3. column
//         0.0, 0.0, 0.0, -2 * zUpperBound * zLowBound / (zUpperBound - zLowBound));

//     // calculate the new vertex
//     gl_Position = aMat4 * trans;
//     gl_Position = gl_Position / gl_Position.w;    
    
// }