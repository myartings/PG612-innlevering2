#include "GUI_Util.h"

namespace gui
{
	glm::mat4 gen_gui_model_matrix( GLuint tex_width, GLuint tex_height )
	{
		return glm::scale(glm::mat4(1), glm::vec3(tex_width, tex_height, 1));
	}

	glm::mat4 translate( glm::mat4& m, glm::vec3& v )
	{
		return glm::translate(m, glm::vec3(v.x/window_width, v.y/window_height, v.z));
	}

	GLuint create_gui_texture()
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

	void LoadTexture(GUITexture* target_image, const std::string& image_to_load)
	{
		std::vector<float> data;

		ILuint ImageName;

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

		target_image->width = ilGetInteger(IL_IMAGE_WIDTH); // getting image width
		target_image->height = ilGetInteger(IL_IMAGE_HEIGHT); // and height
		target_image->components = ilGetInteger(IL_IMAGE_CHANNELS);

		data.resize(target_image->width*target_image->height*target_image->components);

		if(target_image->components == 3)
			ilCopyPixels(0, 0, 0, target_image->width, target_image->height, 1, IL_RGB, IL_UNSIGNED_BYTE, data.data());
		else if(target_image->components == 4)
			ilCopyPixels(0, 0, 0, target_image->width, target_image->height, 1, IL_RGBA, IL_UNSIGNED_BYTE, data.data());

		ilDeleteImages(1, &ImageName);
		ilDisable(IL_ORIGIN_SET);
		glBindTexture(GL_TEXTURE_2D, target_image->image);

		if(target_image->components == 3)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, target_image->width, target_image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, data.data());
		else if(target_image->components == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, target_image->width, target_image->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.data());
	}

	GUITexture_ptr load_gui_texture( const std::string& texture_path )
	{
		std::vector<float> data;
		GUITexture_ptr gui_texture = std::make_shared<GUITexture>();
		gui_texture->image = create_gui_texture();

		ILuint ImageName;

		ilGenImages(1, &ImageName); // Grab a new image name.
		ilBindImage(ImageName); 
		ilEnable(IL_ORIGIN_SET);
		ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
		if (!ilLoadImage(texture_path.c_str())) {
			ILenum e;
			std::stringstream error;
			while ((e = ilGetError()) != IL_NO_ERROR) {
				error << e << ": " << iluErrorString(e) << std::endl;
			}
			ilDeleteImages(1, &ImageName); // Delete the image name. 
			throw std::runtime_error(error.str());
		}

		gui_texture->width = ilGetInteger(IL_IMAGE_WIDTH); // getting image width
		gui_texture->height = ilGetInteger(IL_IMAGE_HEIGHT); // and height
		gui_texture->components = ilGetInteger(IL_IMAGE_CHANNELS);

		data.resize(gui_texture->width*gui_texture->height*gui_texture->components);

		if(gui_texture->components == 3)
			ilCopyPixels(0, 0, 0, gui_texture->width, gui_texture->height, 1, IL_RGB, IL_UNSIGNED_BYTE, data.data());
		else if(gui_texture->components == 4)
			ilCopyPixels(0, 0, 0, gui_texture->width, gui_texture->height, 1, IL_RGBA, IL_UNSIGNED_BYTE, data.data());

		ilDeleteImages(1, &ImageName);
		ilDisable(IL_ORIGIN_SET);
		glBindTexture(GL_TEXTURE_2D, gui_texture->image);

		if(gui_texture->components == 3)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, gui_texture->width, gui_texture->height, 0, GL_RGB, GL_UNSIGNED_BYTE, data.data());
		else if(gui_texture->components == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, gui_texture->width, gui_texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.data());

		gui_texture->model_matrix = gen_gui_model_matrix(gui_texture->width, gui_texture->height);
		return gui_texture;
	}



}