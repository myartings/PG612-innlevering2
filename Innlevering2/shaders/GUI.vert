#version 150

uniform mat4 model_matrix;
uniform mat4 projection;
uniform mat4 view;

in  vec2 in_Position;
out vec2 ex_texcoord;

void main() {	
	vec4 pos = vec4(in_Position.x, in_Position.y, 1, 1);
	gl_Position = projection * view * model_matrix * pos;

	ex_texcoord = in_Position;// 0.5*in_Position+vec2(0.5);

}