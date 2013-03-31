#version 150
 
layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

smooth in vec3 g_n[3];
smooth in vec3 g_v[3];
smooth in vec3 g_l[3];
smooth in vec4 g_shadow_coord[3];

smooth out vec3 f_n;
smooth out vec3 f_v;
smooth out vec3 f_l;
smooth out vec4 f_shadow_coord;

smooth out vec3 beyer_coord;
flat out vec3 vertex_pos;

void main() {

	for(int i = 0; i < gl_in.length(); i++)
	{
		beyer_coord = vec3((i+1)==1?1:0, (i+1)==2?2:0, (i+1)==3?3:0);

		f_n = g_n[i];
		f_v = g_v[i];
		f_l = g_l[i];
		f_shadow_coord = g_shadow_coord[i];

		gl_Position =  gl_in[i].gl_Position;
		EmitVertex();
	}

	EndPrimitive();
}