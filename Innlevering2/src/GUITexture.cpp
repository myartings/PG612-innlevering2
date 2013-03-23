#include "GUITexture.h"

namespace gui
{
	//GUITexture::GUITexture()
	//{	
	//	position = glm::vec3(0);
	//	dimensions = glm::vec3(0);
	//}

	GUITexture::GUITexture(const std::string& texture_path )
	{
		texture = LoadTexture(texture_path);
		dimensions = glm::vec3(texture.width, texture.height, 1.0f);
		position = glm::vec3(0);
		scale = glm::vec3(1);
		rect = Rect(0.0f, 0.0f, dimensions.x, dimensions.y);
	}

	GUITexture::~GUITexture()
	{
		
	}

	void GUITexture::translate( glm::vec2& v )
	{
		position += glm::vec3(v.x, v.y, 0);
		set_position(position);
	}

	void GUITexture::translate( glm::vec3& v )
	{
		position += v;
		set_position(position);
	}

	void GUITexture::set_position( glm::vec2& v )
	{
		position = glm::vec3(v.x, v.y, -5.0f);
		set_position(position);
	}

	void GUITexture::set_position( glm::vec3& v )
	{
		position = v;
		position_2d = glm::vec2(v.x, v.y);
		model_matrix = glm::translate(glm::mat4(1), position); 
		model_matrix = glm::scale(model_matrix, dimensions);
		model_matrix = glm::scale(model_matrix, scale);
		rect.x = position.x;
		rect.y = position.y;
	}

	void GUITexture::set_scale( glm::vec2& v )
	{
		scale = glm::vec3(v.x, v.y, 1.0f);
		model_matrix = glm::translate(glm::mat4(1), position); 
		model_matrix = glm::scale(model_matrix, dimensions);
		model_matrix = glm::scale(model_matrix, scale);
		rect.width*=scale.x;
		rect.height*=scale.y;
	}

	bool GUITexture::contains( glm::vec2& v )
	{
		return Rect::contains(rect, v);
	}

	void GUITexture::Draw( std::shared_ptr<GLUtils::Program> gui_program )
	{
		gui_program->use();
		glActiveTexture(GL_TEXTURE0);

		glBindTexture(GL_TEXTURE_2D, texture.image);

		glUniformMatrix4fv(gui_program->getUniform("model_matrix"), 1, 0, glm::value_ptr(model_matrix));
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		glBindTexture(GL_TEXTURE_2D, 0);
		gui_program->disuse();
	}

	glm::vec3& GUITexture::get_position()
	{
		return position;
	}

	glm::vec2& GUITexture::get2d_position()
	{
		return position_2d;
	}

	gui::Rect& GUITexture::get_rect()
	{
		return rect;
	}

}