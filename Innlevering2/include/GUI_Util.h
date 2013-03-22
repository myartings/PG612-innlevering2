#ifndef GUI_Util_H
#define GUI_Util_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform2.hpp>
#include <gl/glew.h>

#include <IL/il.h>
#include <IL/ilu.h>
#include <iostream>
#include <strstream>
#include <vector>
#include <stdexcept>

#include "Game_Constants.h"
#include "GLUtils/GLUtils.hpp"

using std::cerr;
using std::endl;
using GLUtils::checkGLErrors;

/**
* The namespace contains functions to make "GUI" texture displaying easier.
*/
namespace gui
{
	/**
	*A wrapper struct meant to hold information for a glTexture2D object,
	*including the image ID, it's width, height and number of components
	*/
	struct Texture
	{
		Texture()
		{
			image = -1;
			width = -1;
			height = -1;
			components = -1;
		}

		GLuint image;
		GLuint width;
		GLuint height;
		GLuint components;
	};
	
	/**
	* A simple rect structure to hold the position and dimensions of something
	* 
	*/
	struct Rect
	{
		Rect();
		Rect(int x, int y, int width, int height);
		
		/**
		* @return true if the rect r1 contains the vector v2, false otherwise
		*/
		static bool contains(Rect& r, glm::vec2& v);
		
		int x;
		int y;
		int width;
		int height;
	};

	/**
	* Generates a GL_TEXTURE_2D with glTexParameteri values suiting GUI textures
	*/
	GLuint create_texture();

	/**
	* Loads the desired texture using DevIL.
	*
	* @returns a Texture object containing openGL image ID, and the
	* width, height and number of components of the image
	*/
	Texture LoadTexture(const std::string& image_to_load);

}
#endif // GUI_Util_H
