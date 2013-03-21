#include "SliderWithText.h"

TextureLoader::Image SliderWithText::slider_texture;
TextureLoader::Image SliderWithText::slider_knob_texture;
GLuint SliderWithText::gui_vbo = -1;
GLuint SliderWithText::gui_vao = -1;

SliderWithText::SliderWithText(std::string name_label_path,std::shared_ptr<GLUtils::Program> gui_program)
{
	if(slider_texture.components == -1 && slider_knob_texture.components == -1)
		LoadSliderTextures();
	if(gui_vao == -1 && gui_vbo == -1)
		GenerateGUI_VBO_VAO(gui_program);

	glGenTextures(1, &label_texture.image);
	glBindTexture(GL_TEXTURE_2D, label_texture.image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	TextureLoader::LoadTexture(&label_texture, name_label_path);
	glBindTexture(GL_TEXTURE_2D, 0);
}

SliderWithText::~SliderWithText()
{
}

void SliderWithText::LoadSliderTextures()
{

	glGenTextures(1, &slider_texture.image);
	glBindTexture(GL_TEXTURE_2D, slider_texture.image);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	TextureLoader::LoadTexture(&slider_texture,"GUI/Slider_line.png");

	glGenTextures(1, &slider_knob_texture.image);
	glBindTexture(GL_TEXTURE_2D, slider_knob_texture.image);

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

	//Bind the textures before rendering
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(gui_vao);

	float downscale = 1.0f/label_texture.width;
	model_matrix = glm::scale(glm::mat4(1), glm::vec3(label_texture.width*downscale, label_texture.height*downscale, 1));
	model_matrix = glm::translate(model_matrix, glm::vec3(0, 0, -10));

	glUniformMatrix4fv(gui_program->getUniform("model_matrix"), 1, 0, glm::value_ptr(model_matrix));
	glBindTexture(GL_TEXTURE_2D, label_texture.image);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	CHECK_GL_ERRORS();

	downscale = 1.0f/slider_texture.width;
	model_matrix = glm::scale(glm::mat4(1), glm::vec3(slider_texture.width*downscale, slider_texture.height*downscale, 1));
	model_matrix = glm::translate(model_matrix, glm::vec3(0, -1,-10));
	glUniformMatrix4fv(gui_program->getUniform("model_matrix"), 1, 0, glm::value_ptr(model_matrix));

	glBindTexture(GL_TEXTURE_2D, slider_texture.image);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);


	float xdownscale = 1.0f/slider_knob_texture.width;
	float ydownscale = 1.0f/slider_knob_texture.height;
	model_matrix = glm::scale(glm::mat4(1), glm::vec3(slider_knob_texture.width*downscale, slider_knob_texture.height*ydownscale, 1));

	model_matrix = glm::scale(model_matrix, glm::vec3(0.1));
	model_matrix = glm::translate(model_matrix, glm::vec3(0, -1, -10));
	glUniformMatrix4fv(gui_program->getUniform("model_matrix"), 1, 0, glm::value_ptr(model_matrix));
	glBindTexture(GL_TEXTURE_2D, slider_knob_texture.image);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	//Unbind the textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);

	gui_program->disuse();
}

void SliderWithText::Update( float delta_time )
{

}

