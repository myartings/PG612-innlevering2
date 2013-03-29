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