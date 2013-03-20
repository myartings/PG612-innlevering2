#version 150
uniform sampler2DShadow shadowmap_texture;
uniform vec3 color;

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

	float shade_factor = textureProj(shadowmap_texture, f_shadow_coord);

	shade_factor = shade_factor * 0.25 + 0.75;

	vec4 diffuse = vec4(diff*color, 1.0);
    float spec = pow(max(0.0f, dot(n, h)), 128.0f);

	float k = min(min(beyer_coord.x, beyer_coord.y), beyer_coord.z);

	out_color = vec4( ( (diff*color) + (spec*0.1) ) * shade_factor, 1.0);

	if(k<0.03 )
		out_color = vec4( out_color.xyz * amplify(k, 40, -0.5), 1);
}