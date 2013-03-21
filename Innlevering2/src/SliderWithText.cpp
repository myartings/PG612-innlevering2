#include "SliderWithText.h"

GLuint SliderWithText::slider_texture = -1;
GLuint SliderWithText::slider_knob_texture = -1;
GLuint SliderWithText::gui_vbo = -1;
GLuint SliderWithText::gui_vao = -1;

SliderWithText::SliderWithText(std::string name_label_path,std::shared_ptr<GLUtils::Program> gui_program)
{
	if(slider_texture == -1 && slider_knob_texture == -1)
		LoadSliderTextures();
	if(gui_vao == -1 && gui_vbo == -1)
		GenerateGUI_VBO_VAO(gui_program);

	glGenTextures(1, &label_texture);
	glBindTexture(GL_TEXTURE_2D, label_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	TextureLoader::LoadTexture(&label_texture,name_label_path);
	glBindTexture(GL_TEXTURE_2D, 0);
}

SliderWithText::~SliderWithText()
{
}

void SliderWithText::LoadSliderTextures()
{

	glGenTextures(1, &slider_texture);
	glBindTexture(GL_TEXTURE_2D, slider_texture);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	TextureLoader::LoadTexture(&slider_texture,"GUI/Slider_line.png");

	glGenTextures(1, &slider_knob_texture);
	glBindTexture(GL_TEXTURE_2D, slider_knob_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	TextureLoader::LoadTexture(&slider_knob_texture,"GUI/Slider_knob.png");
	
	glBindTexture(GL_TEXTURE_2D, 0);
	model_matrix = glm::mat4(1);
}

void SliderWithText::GenerateGUI_VBO_VAO(std::shared_ptr<GLUtils::Program> gui_program)
{
	glGenVertexArrays(1, &gui_vao);
	glBindVertexArray(gui_vao);
	static float positions[8] = {
		-1.0, 1.0,
		-1.0, -1.0,
		1.0, 1.0,
		1.0, -1.0,
	};

	glGenBuffers(1, &gui_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, gui_vbo);
	glBufferData(GL_ARRAY_BUFFER, 4*2*sizeof(float), &positions[0], GL_STATIC_DRAW);
	gui_program->setAttributePointer("in_Position", 2, GL_FLOAT, GL_FALSE, 0, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SliderWithText::Draw( glm::vec2 position, GLuint& quad_fbo,
						std::shared_ptr<GLUtils::Program> gui_program)
{
	gui_program->use();
	model_matrix = glm::mat4(1);
	model_matrix = glm::scale(model_matrix, glm::vec3(0.3));

	//Bind the textures before rendering
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(gui_vao);
CHECK_GL_ERRORS();
	model_matrix = glm::translate(model_matrix, glm::vec3(0, 0, -10));
	glUniformMatrix4fv(gui_program->getUniform("model_matrix"), 1, 0, glm::value_ptr(model_matrix));
	glBindTexture(GL_TEXTURE_2D, label_texture);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	CHECK_GL_ERRORS();

	model_matrix = glm::translate(model_matrix, glm::vec3(0, -1, 0));
	glUniformMatrix4fv(gui_program->getUniform("model_matrix"), 1, 0, glm::value_ptr(model_matrix));
	glBindTexture(GL_TEXTURE_2D, slider_texture);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);


	model_matrix = glm::translate(model_matrix, glm::vec3(0, -1, 0));
	glUniformMatrix4fv(gui_program->getUniform("model_matrix"), 1, 0, glm::value_ptr(model_matrix));
	glBindTexture(GL_TEXTURE_2D, slider_knob_texture);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	//Unbind the textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);

	gui_program->disuse();
}

void SliderWithText::Update( float delta_time )
{

}

