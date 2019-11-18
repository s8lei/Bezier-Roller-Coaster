#version 330 core
// This is a sample fragment shader.

// Inputs to the fragment shader are the outputs of the same name from the vertex shader.
// Note that you do not have access to the vertex shader's default output, gl_Position.
out vec4 FragColor;

in vec3 TexCoords;

uniform vec3 color;
uniform samplerCube skybox;

void main()
{
    FragColor = texture(skybox, TexCoords);
    //FragColor = vec4(TexCoords,1);
}
