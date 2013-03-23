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


	Rect::Rect()
	{
		x = 0;
		y = 0;
		width = 0;
		height = 0;
	}

	Rect::Rect( float x, float y, float width, float height )
	{
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}


	bool Rect::contains( Rect& r, glm::vec2& v )
	{
		if(v.x > (r.x + r.width))
			return false;
		else if(v.y > (r.y + r.height))
			return false;
		else if(v.x < r.x)
			return false;
		else if(v.y < r.y)
			return false;
		else
			return true;
	}

}