#version 130
uniform mat4 modelviewprojection_matrix;

in  vec3 in_Position;

void main(){
	gl_Position = modelviewprojection_matrix * vec4(in_Position, 1.0f);

}