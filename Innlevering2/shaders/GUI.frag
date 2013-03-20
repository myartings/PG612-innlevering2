#version 150
uniform sampler2D texture;

in vec2 ex_texcoord;

out vec4 res_Color;

void main() {
	res_Color = texture2D(texture, ex_texcoord.xy);
}