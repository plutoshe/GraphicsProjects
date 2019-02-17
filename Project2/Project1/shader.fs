#version 330

in vec2 TexCoord0;

out vec4 FragColor;

struct DirectionalLight
{
    vec3 Color;
    float AmbientIntensity;
};

uniform DirectionalLight gDirectionalLight;
uniform sampler2D gSampler;

void main()
{
    FragColor = texture2D(gSampler, TexCoord0.xy) *
            vec4(gDirectionalLight.Color, 1.0f) *
            gDirectionalLight.AmbientIntensity;
}
// in vec4 Color;

// out vec4 FragColor;

// void main()
// {
//     FragColor = Color;
// }
// #version 330 core
// //uniform vec4 inputColor;
// out vec4 FragColor;


// void main()
// {
//     FragColor = vec4(0.5f,0.5f,0.5f,1.f);
// } 