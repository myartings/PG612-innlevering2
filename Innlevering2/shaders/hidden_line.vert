#version 150
uniform mat4 modelviewprojection_matrix;
uniform mat4 modelview_matrix_inverse;
uniform mat4 light_matrix;
uniform vec3 light_pos;
uniform mat4 shadow_matrix;

in vec3 position;
in vec3 normal;

smooth out vec4 g_shadow_coord;

smooth out vec3 g_v;
smooth out vec3 g_l;
smooth out vec3 g_n;

void main() {	
	float homogeneous_divide = (1.0f/modelview_matrix_inverse[3].w);
	vec3 cam_pos_world = modelview_matrix_inverse[3].xyz*homogeneous_divide;

	g_v = normalize(cam_pos_world - position);
	g_l = normalize(light_pos - position);
	g_n = normalize(normal);

	gl_Position = modelviewprojection_matrix * vec4(position, 1.0);

	g_shadow_coord = shadow_matrix * vec4(position, 1.0);
}