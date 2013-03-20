#include "SliderWithText.h"

GLuint SliderWithText::slider_texture = -1;
GLuint SliderWithText::slider_knob_texture = -1;

SliderWithText::SliderWithText(std::string name_label_path)
{
	if(slider_texture == -1 && slider_knob_texture == -1)
		LoadSliderTextures();

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

void SliderWithText::Draw( glm::vec2 position, GLuint& quad_fbo,
						std::shared_ptr<GLUtils::Program> gui_program)
{
	gui_program->use();
	glUniformMatrix4fv(gui_program->getUniform("model_matrix"), 1, 0, glm::value_ptr(model_matrix));

	//Bind the textures before rendering
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, label_texture);

	glBindVertexArray(quad_fbo);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	//Unbind the textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);

	gui_program->disuse();
}

void SliderWithText::Update( float delta_time )
{

}

