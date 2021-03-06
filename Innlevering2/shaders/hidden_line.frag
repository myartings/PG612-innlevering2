#version 150
uniform sampler2DShadow shadowmap_texture;
uniform samplerCube diffuse_map;
uniform float diffuse_mix_value;
uniform vec3 color;

uniform float line_threshold;
uniform float line_scale;
uniform float line_offset;

smooth in vec4 f_shadow_coord;

smooth in vec3 f_n;
smooth in vec3 f_v;
smooth in vec3 f_l;
smooth in vec3 beyer_coord;

out vec4 out_color;

float amplify(float d, float scale, float offset) {
	d= scale * d + offset;
	d= clamp(d, 0, 1);
	d = 1-exp2(- 2*d*d);
	return d;
}

void main() {
	vec3 l = normalize(f_l);
    vec3 h = normalize(normalize(f_v)+l);
    vec3 n = normalize(f_n);
	
	float diff = max(0.0f, dot(n, l));
	float spec = pow(max(0.0f, dot(n, h)), 128.0f);
	vec3 diffuse = vec3(diff*color);

	ivec2 o = ivec2(mod(floor(gl_FragCoord.xy), 2.0));
	float shade_factor = textureProjOffset(shadowmap_texture, f_shadow_coord, ivec2(-1, -1)+o);
	shade_factor += textureProjOffset(shadowmap_texture, f_shadow_coord, ivec2(1, -1)+o);
	shade_factor += textureProjOffset(shadowmap_texture, f_shadow_coord, ivec2(-1, 1)+o);
	shade_factor += textureProjOffset(shadowmap_texture, f_shadow_coord, ivec2(1, 1)+o);
	shade_factor = shade_factor * 0.25 + 0.75;

	float k = min(min(beyer_coord.x, beyer_coord.y), beyer_coord.z);

	vec3 diff_cubemap_color = texture(diffuse_map, n).xyz;
	diff_cubemap_color = mix(diff_cubemap_color, diffuse, diffuse_mix_value);

	out_color = vec4( ( (diff_cubemap_color*color) + (spec*0.1) ) * shade_factor, 1.0);

	if(k < line_threshold )
		out_color = vec4( out_color.xyz * amplify(k, line_scale, line_offset), 1.0);
}