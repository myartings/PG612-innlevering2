#version 150
uniform sampler2DShadow shadowmap_texture;
uniform samplerCube diffuse_map;

uniform vec3 color;

smooth in vec4 f_shadow_coord;

smooth in vec3 f_n;
smooth in vec3 f_v;
smooth in vec3 f_l;

out vec4 out_color;

void main() {
	vec3 l = normalize(f_l);
    vec3 h = normalize(normalize(f_v)+l);
    vec3 n = normalize(f_n);
	
	float diff = max(0.0f, dot(n, l));
	float spec = pow(max(0.0f, dot(n, h)), 128.0f);

	ivec2 o = ivec2(mod(floor(gl_FragCoord.xy), 2.0));
	float shade_factor;

	shade_factor = textureProj(shadowmap_texture, f_shadow_coord);
	int aliasing_number = 1;
	for(int i = 0; i < aliasing_number; i++)
	{
		shade_factor += textureProjOffset(shadowmap_texture, f_shadow_coord, ivec2(-1-i, -1-i)+o);
		shade_factor += textureProjOffset(shadowmap_texture, f_shadow_coord, ivec2(1+i, -1-i)+o);
		shade_factor += textureProjOffset(shadowmap_texture, f_shadow_coord, ivec2(-1-i, 1+i)+o);
		shade_factor += textureProjOffset(shadowmap_texture, f_shadow_coord, ivec2(1+i, 1+i)+o);
	}

	shade_factor = shade_factor * (0.25/aliasing_number) + 0.75;

	vec3 diff_cubemap_color = texture(diffuse_map, n).xyz;
    out_color = vec4( ( (diff_cubemap_color*color) + (spec*0.1) ) * shade_factor, 1.0);
}