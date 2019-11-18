#version 330 core
// This is a sample fragment shader.

// Inputs to the fragment shader are the outputs of the same name from the vertex shader.
// Note that you do not have access to the vertex shader's default output, gl_Position.
out vec4 FragColor;

in vec3 Normal;
in vec3 Position;
in vec3 Color;

uniform vec3 cameraPos;
uniform samplerCube skybox;
uniform bool isCP;
uniform vec3 color;

void main()
{
    vec3 I = normalize(Position - cameraPos);
    vec3 R = reflect(I, normalize(Normal));
    if (isCP)
        FragColor = vec4(Color, 1.0);
    else
        FragColor = vec4(texture(skybox, R).rgb, 1.0);
}
