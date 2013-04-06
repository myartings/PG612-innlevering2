#version 130

uniform mat4 modelviewprojection_matrix;
in  vec2 in_Position;
out vec2 ex_texcoord;

void main(){
	vec4 pos = vec4(in_Position.x, in_Position.y, 0.5, 1);
	gl_Position = modelviewprojection_matrix*pos;//projection * view * model_matrix * pos;
	ex_texcoord = 0.5*in_Position+vec2(0.5);
}