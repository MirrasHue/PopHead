#version 330 core

out vec4 fragColor;

in vec2 texCoords;

uniform sampler2D image;
uniform vec4 color;

void main()
{
	fragColor = vec4(color.rgb, texture(image, texCoords).r * color.a);
}

