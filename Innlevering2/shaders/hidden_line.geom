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

/*-----------0---------------*/
	beyer_coord = vec3(1, 0, 0);

	f_n = g_n[0];
	f_v = g_v[0];
	f_l = g_l[0];
	f_shadow_coord = g_shadow_coord[0];

	gl_Position =  gl_in[0].gl_Position;
	EmitVertex();
/*-----------end---------------*/




/*-----------1---------------*/		
	beyer_coord = vec3(0, 1, 0);
	
	f_n = g_n[1];
	f_v = g_v[1];
	f_l = g_l[1];
	f_shadow_coord = g_shadow_coord[1];
	
	gl_Position =  gl_in[1].gl_Position;
	EmitVertex();
/*-----------end---------------*/




/*-----------2---------------*/
	beyer_coord = vec3(0, 0, 1);

	f_n = g_n[2];
	f_v = g_v[2];
	f_l = g_l[2];
	f_shadow_coord = g_shadow_coord[2];

	gl_Position =  gl_in[2].gl_Position;
	EmitVertex();
/*-----------end---------------*/
	EndPrimitive();
}