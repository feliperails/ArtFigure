#version 330 core
in vec4 TexCoord;

out vec4 color;

uniform sampler2D ourTexture1;

void main()
{
    color = TexCoord;
}