#version 150
uniform sampler2D texture;
uniform float gui_alpha;
in vec2 ex_texcoord;

out vec4 res_Color;

void main() {
	vec4 texture_color = texture2D(texture, ex_texcoord.xy);
	res_Color = vec4(texture_color*vec4(1,1,1,gui_alpha));
}