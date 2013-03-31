#version 130

uniform sampler2D fbo_texture;
uniform float gui_alpha;
in vec2 ex_texcoord;
out vec4 res_Color;

float NormalizeDepth(float depth_val){
		float near_clip = 0.5;
		float far_clip = 30.0; 
		return (2.0 * near_clip) / (far_clip + near_clip - depth_val * (far_clip - near_clip));
	}

void main() {
	float depth = texture2D(fbo_texture, ex_texcoord.xy).r;
	depth = NormalizeDepth(depth);
	res_Color = vec4(depth, depth, depth, gui_alpha);
}