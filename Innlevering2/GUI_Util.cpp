#include "GUI_Util.h"

namespace gui
{
	glm::mat4 gen_gui_model_matrix( GLuint tex_width, GLuint tex_height )
	{
		return glm::scale(glm::mat4(1), glm::vec3(tex_width, tex_height, 1));
	}

	GLuint create_texture()
	{
		GLuint texture;

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glBindTexture(GL_TEXTURE_2D, 0);

		return texture;
	}

	Texture LoadTexture(const std::string& image_to_load)
	{
		std::vector<float> data;
		Texture ret_tex;
		ILuint ImageName;
		ret_tex.image = create_texture();
		ilGenImages(1, &ImageName); // Grab a new image name.
		ilBindImage(ImageName); 
		ilEnable(IL_ORIGIN_SET);
		ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
		if (!ilLoadImage(image_to_load.c_str())) {
			ILenum e;
			std::stringstream error;
			while ((e = ilGetError()) != IL_NO_ERROR) {
				error << e << ": " << iluErrorString(e) << std::endl;
			}
			ilDeleteImages(1, &ImageName); // Delete the image name. 
			throw std::runtime_error(error.str());
		}

		ret_tex.width = ilGetInteger(IL_IMAGE_WIDTH); // getting image width
		ret_tex.height = ilGetInteger(IL_IMAGE_HEIGHT); // and height
		ret_tex.components = ilGetInteger(IL_IMAGE_CHANNELS);

		data.resize(ret_tex.width*ret_tex.height*ret_tex.components);

		if(ret_tex.components == 3)
			ilCopyPixels(0, 0, 0, ret_tex.width, ret_tex.height, 1, IL_RGB, IL_UNSIGNED_BYTE, data.data());
		else if(ret_tex.components == 4)
			ilCopyPixels(0, 0, 0, ret_tex.width, ret_tex.height, 1, IL_RGBA, IL_UNSIGNED_BYTE, data.data());

		ilDeleteImages(1, &ImageName);
		ilDisable(IL_ORIGIN_SET);
		glBindTexture(GL_TEXTURE_2D, ret_tex.image);

		if(ret_tex.components == 3)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ret_tex.width, ret_tex.height, 0, GL_RGB, GL_UNSIGNED_BYTE, data.data());
		else if(ret_tex.components == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ret_tex.width, ret_tex.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.data());

		return ret_tex;
	}

	GUITexture::GUITexture()
	{	
		position = glm::vec3(0);
		dimensions = glm::vec3(0);
	}

	GUITexture::GUITexture( std::string& texture_path )
	{
		texture = LoadTexture(texture_path);
		dimensions = glm::vec3(texture.width, texture.height, 1.0f);
		position = glm::vec3(0);
	}

	GUITexture::~GUITexture()
	{
	}

	void GUITexture::translate( glm::vec2 v )
	{
		position += glm::vec3(v.x, v.y, 0);
		model_matrix = glm::translate(model_matrix, position); 
		model_matrix = glm::scale(model_matrix, dimensions);
	}

	void GUITexture::translate( glm::vec3 v )
	{
		position += v;
		model_matrix = glm::translate(model_matrix, position); 
		model_matrix = glm::scale(model_matrix, dimensions);
	}

	void GUITexture::set_position( glm::vec2 v )
	{
		position = glm::vec3(v.x, v.y, -5.0f);
		model_matrix = glm::translate(model_matrix, position); 
		model_matrix = glm::scale(model_matrix, dimensions);
	}

	void GUITexture::set_position( glm::vec3 v )
	{
		position = v;
		model_matrix = glm::translate(model_matrix, position); 
		model_matrix = glm::scale(model_matrix, dimensions);
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

	void GUITexture::set_scale( glm::vec2 v )
	{
		dimensions = glm::vec3(v.x, v.y, 1.0f);
	}

}