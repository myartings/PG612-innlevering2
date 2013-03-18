#version 150
uniform samplerCube cubemap;

smooth in vec3 pass_n;
smooth in vec3 pass_v;

out vec4 out_color;

void main() {
	const float eta_air = 1.000293;
	const float eta_carbondioxide = 1.00045;
	const float eta_water = 1.3330;
	const float eta_ethanol = 1.361;
	const float eta_pyrex = 1.470;
	const float eta_diamond = 2.419;

	const float eta0 = eta_air;
	const float eta1 = eta_carbondioxide;

	const float eta = eta0/eta1;
	const float eta_r = eta+0.02;
	const float eta_g = eta;
	const float eta_b = eta-0.02;

	const float R0 = pow((eta0 - eta1) / (eta0 + eta1), 2);

	vec3 n = normalize(pass_n);
	vec3 v = normalize(pass_v);

	//FIXME: Implement lookup into the cube map and fresnel rendering
	vec3 texcoord_reflect = reflect(-v, n);
	
	vec3 texcoord_refract_r = refract(-v, n, eta_r);
	vec3 texcoord_refract_g = refract(-v, n, eta_g);
	vec3 texcoord_refract_b = refract(-v, n, eta_b);

	vec4 reflect_vec = texture(cubemap, texcoord_reflect);

	float color_r = texture(cubemap, texcoord_refract_r).r;
	float color_g = texture(cubemap, texcoord_refract_g).g;
	float color_b = texture(cubemap, texcoord_refract_b).b;

	vec4 refract_color = vec4(color_g, color_g, color_b, 1.0);

	float frensel = R0 + (1.0-R0)*pow((1.0-dot(v, n)), 5.0);

	//vec4 chromatic_refract = vec4(refract_vec.x*0.5, refract_vec.y*0.7, refract_vec.z*1, refract_vec.z);
	out_color = mix(refract_color, reflect_vec, frensel);
	//out_color = vec4(vec3(dot(n, v)), 1.0);
}