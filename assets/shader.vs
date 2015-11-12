#version 330

in vec4 position;
uniform vec2 offset;

void main()
{
	gl_Position = position;
	gl_Position.xy += offset;
}