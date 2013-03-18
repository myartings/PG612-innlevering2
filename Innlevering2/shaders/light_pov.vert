#version 130

//uniform mat4 projection;
uniform mat4 modelviewprojection_matrix;

in  vec3 in_Position;

void main(){
	//vec4 pos = vec4(in_Position.x, in_Position.y, 0.5, 1);
	gl_Position = modelviewprojection_matrix * vec4(in_Position, 1.0f);//pos;

}